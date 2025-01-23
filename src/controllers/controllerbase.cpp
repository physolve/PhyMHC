#include "controllerbase.h"
#include <windows.h>
#include <QDebug>

BYTE m_byAITotal;
BYTE m_byDOTotal;

ControllerBase::ControllerBase(QObject *parent) : 
    QObject(parent), connectionState(false)
{
    // connect(m_timer, &QTimer::timeout, this, &ControllerBase::processEvents);
}

ControllerBase::~ControllerBase(){
    qDebug() << "ControllerBase destructor";
}

void ControllerBase::startTest(){
}

bool ControllerBase::isConnected(){
    return connectionState;
}

IcpAICtrl::IcpAICtrl(QList<QSharedPointer<ControllerData>> dataStorage, QObject *parent) : 
    ControllerBase(parent), USB_AI(nullptr), m_timer(new QTimer)
{
    name = "IcpAICtrl";

    time = dataStorage[0];

    tcUp = dataStorage[1];
    prUp = dataStorage[2];
    flUp = dataStorage[3];

    tcDw = dataStorage[4];
    prDw = dataStorage[5];
    flDw = dataStorage[6];
    
    connect(m_timer, &QTimer::timeout, this, &IcpAICtrl::processEvents);
}

IcpAICtrl::~IcpAICtrl(){
    CloseDevice(USB_AI);
    USB_AI = nullptr;
    if(m_timer->isActive()) m_timer->stop();
    qDebug() << "IcpAICtrl destructor";
}

int IcpAICtrl::initUSBAI(){
    int iErrCode;
    WORD wFWVer;
    BYTE bySupIOMask, byDeviceNickName[32], byDeviceSN[32];

    USB_AI = CreateInstance();
    
    if(ERR_NO_ERR != (iErrCode = OpenDevice(USB_AI, USB2019, 1))){
        char szMessage[10];
        qDebug() << QString("OpenDevice error [%1]").arg(iErrCode);
        CloseDevice(USB_AI);
        getchar();
        return -1;
    }
    connectionState = true;
    // GetFwVer(USB_AI, &wFWVer);

    GetSupportIOMask(USB_AI, &bySupIOMask);
    GetDeviceNickName(USB_AI, byDeviceNickName);
    GetDeviceSN(USB_AI, byDeviceSN);

    GetAITotal(USB_AI, &m_byAITotal);
    return 0;
}

void IcpAICtrl::tempFunctionToSetChannelsType(){
    int iErrCode;
    // this function set Type K thermocouple Type to channel 0
    // other types are: 0x08 -> -10 V ~ +10 V, 0x09 -> -5 V ~ +5 V, 0x1A  -> 0 ~ +20 mA 
    if(ERR_NO_ERR != (iErrCode = AI_SetTypeCode(USB_AI, 0, 0x0F))){
        qDebug() << QString::number(iErrCode);
    }
}

void IcpAICtrl::startTest(){
    m_programmTime.start();
    m_timer->start(1000);
}

void IcpAICtrl::processEvents(){
    int iErrCode;
    float o_fAIValue[USBIO_AI_MAX_CHANNEL];

    if(ERR_NO_ERR != (iErrCode = AI_ReadValueAnalog(USB_AI, o_fAIValue))){
        qDebug() << QString::number(iErrCode);
        connectionState = false;
        // emit disconnect state
    }
    else{
        for(auto iIdx = 0; iIdx < USBIO_AI_MAX_CHANNEL; iIdx++){
            qDebug() << QString::number(o_fAIValue[iIdx]);
        }
    }
    emit valueChanged();   
}

IcpDOCtrl::IcpDOCtrl(const QList<Switch> &switches, QObject *parent) : 
    ControllerBase(parent), USB_DO(nullptr)
{
    name = "IcpDOCtrl";

    m_switches = switches;
}

IcpDOCtrl::~IcpDOCtrl(){
    CloseDevice(USB_DO);
    USB_DO = nullptr;
    qDebug() << "IcpDOCtrl destructor";
}

int IcpDOCtrl::initUSBDO(){
    int iErrCode;
    WORD wFWVer;
    BYTE bySupIOMask, byDeviceNickName[32], byDeviceSN[32];

    USB_DO = CreateInstance();

    if(ERR_NO_ERR != (iErrCode = OpenDevice(USB_DO, USB2045, 1))){
        char szMessage[10];
        qDebug() << QString("OpenDevice error [%1]").arg(iErrCode);
        CloseDevice(USB_DO);
        getchar();
        return -1;
    }

    GetSupportIOMask(USB_DO, &bySupIOMask);
    GetDeviceNickName(USB_DO, byDeviceNickName);
    GetDeviceSN(USB_DO, byDeviceSN);

    GetDOTotal(USB_DO, &m_byDOTotal);
    return 0;
}

void IcpDOCtrl::startTest(){
    BYTE o_byDORead[2];
    
    DO_ReadValue(USB_DO, o_byDORead);

    QVector<bool> vector;
    for(int j = 0; j < 7; ++j){
        vector.append(o_byDORead[0]>>j&0x1); // from back
    }
    for(int j = 0; j < 2; ++j){
        vector.append(o_byDORead[1]>>j&0x1); // from back
    }
    // auto it_begin = m_switches.begin();
    for(auto i = 0; i < vector.size(); ++i){
        m_switches[i].setState(vector[i]);
    }
}

void IcpDOCtrl::setSwitchList(const QList<Switch> &switches){
    m_switches = switches;
}

QList<Switch> IcpDOCtrl::getSwitchList() const{
    return m_switches;
}