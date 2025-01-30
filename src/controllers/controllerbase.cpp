#include "controllerbase.h"
#if _WIN32
    #define _WINSOCKAPI_
    #include <windows.h>
#elif __linux__
    // any linux related headers
#endif
#include <QDebug>
#include "../icp/Global.h"
// BYTE m_byAITotal;
// BYTE m_byDOTotal;


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

bool ControllerBase::isConnected() const{
    return connectionState;
}

IcpAICtrl::IcpAICtrl(QObject *parent) : 
    ControllerBase(parent), USB_AI(false), m_timer(new QTimer) // USB_AI(nullptr),
{
    name = "IcpAICtrl";
    connect(m_timer, &QTimer::timeout, this, &IcpAICtrl::processEvents);
}

IcpAICtrl::~IcpAICtrl(){

    if(USB_AI){
        // CloseDevice(USB_AI);
        // CloseDevice(USB_AI);
        // USB_AI = nullptr;
        auto res = USBIO_CloseDevice(DevNum);
    }
    if(m_timer->isActive()) m_timer->stop();
    qDebug() << "IcpAICtrl destructor";
}

void IcpAICtrl::setData(ControllerData* ptr, DataType type){
    switch(type){
        case DataType::TYPE_time: time = ptr; break;
        case DataType::TYPE_tcUp: tcUp = ptr; break;
        case DataType::TYPE_prUp: prUp = ptr; break;
        case DataType::TYPE_flUp: flUp = ptr; break;
        case DataType::TYPE_tcDw: tcDw = ptr; break;
        case DataType::TYPE_prDw: prDw = ptr; break;
        case DataType::TYPE_flDw: flDw = ptr; break;
        default: qDebug() << "unknown type";
    }
}

int IcpAICtrl::initUSBAI(){
    //linux base
    int DeviceID = USB2019;
    BYTE BoardID = 0x1;
    BYTE module_name[15], total_ai, o_byAIChStatus[USBIO_AI_MAX_CHANNEL];

	BYTE status[3][15] = {"Channel Good","Channel Over","Channel Under"};
    auto res = USBIO_OpenDevice(DeviceID, BoardID, &DevNum);

    if (res){
        qDebug() << QString("OpenDevice error Erro : 0x%1\r").arg(res);
        res = USBIO_CloseDevice(DevNum);
        return -1;
    }
    // USBIO_ModuleName(DevNum, module_name);
	USBIO_GetAITotal(DevNum, &total_ai);

    //windows base
    // int iErrCode;
    // WORD wFWVer;
    // BYTE bySupIOMask, byDeviceNickName[32], byDeviceSN[32];

    // USB_AI = CreateInstance();
    
    // if(ERR_NO_ERR != (iErrCode = OpenDevice(USB_AI, USB2019, 1))){
    //     char szMessage[10];
    //     qDebug() << QString("OpenDevice error [%1]").arg(iErrCode);
    //     CloseDevice(USB_AI);
    //     USB_AI = nullptr;
    //     return -1;
    // }
    // connectionState = true;
    // // GetFwVer(USB_AI, &wFWVer);

    // GetSupportIOMask(USB_AI, &bySupIOMask);
    // GetDeviceNickName(USB_AI, byDeviceNickName);
    // GetDeviceSN(USB_AI, byDeviceSN);

    // GetAITotal(USB_AI, &m_byAITotal);
    return 0;
}

void IcpAICtrl::tempFunctionToSetChannelsType(){
    // linux base
    auto res = USBIO_AI_SetTypeCodeToChannel(DevNum, 0, 0x0F);
    if (res){
        qDebug() << QString("SetTypeCode error Erro : 0x%1\r").arg(res);
    }
    // windows base
    // int iErrCode;
    // this function set Type K thermocouple Type to channel 0
    // other types are: 0x08 -> -10 V ~ +10 V, 0x09 -> -5 V ~ +5 V, 0x1A  -> 0 ~ +20 mA 
    // if(ERR_NO_ERR != (iErrCode = AI_SetTypeCode(USB_AI, 0, 0x0F))){
    //     qDebug() << QString::number(iErrCode);
    // }
}

void IcpAICtrl::startTest(){
    m_programmTime.start();
    m_timer->start(1000);
}

void IcpAICtrl::processEvents(){
    // linux base
    float o_fAIValue[USBIO_AI_MAX_CHANNEL];
    auto res = USBIO_AI_ReadValueFloat(DevNum, o_fAIValue);
    if (res){
        qDebug() << QString("SetTypeCode error Erro : 0x%1\r").arg(res);
        connectionState = false;
        // emit disconnect state
        return;
    }

    time->addPoint(m_programmTime.elapsed()/1000.);

    // those points should be recalculated inside each

    tcUp->addPoint(o_fAIValue[0]);
    prUp->addPoint(o_fAIValue[1]);
    flUp->addPoint(o_fAIValue[2]);
    tcDw->addPoint(o_fAIValue[3]);
    prDw->addPoint(o_fAIValue[4]);
    flDw->addPoint(o_fAIValue[5]);
    
    emit valueChanged();
    // some ending action check

    // windows base
    // int iErrCode;
    // float o_fAIValue[USBIO_AI_MAX_CHANNEL];
    // if(ERR_NO_ERR != (iErrCode = AI_ReadValueAnalog(USB_AI, o_fAIValue))){
    //     qDebug() << QString::number(iErrCode);
    //     connectionState = false;
    //     // emit disconnect state
    // }
    // else{
    //     for(auto iIdx = 0; iIdx < USBIO_AI_MAX_CHANNEL; iIdx++){
    //         qDebug() << QString::number(o_fAIValue[iIdx]);
    //     }
    // }
    // emit valueChanged();   
}

IcpDOCtrl::IcpDOCtrl(QObject *parent) : 
    ControllerBase(parent), USB_DO(false), m_switchesCnt(0)//USB_DO(nullptr)
{
    name = "IcpDOCtrl";
}

IcpDOCtrl::~IcpDOCtrl(){
    if(USB_DO){
        // CloseDevice(USB_DO);
        // USB_DO = nullptr;
        // USBIO_CloseDevice(DevNum);
        auto res = USBIO_CloseDevice(DevNum);
    }
    qDebug() << "IcpDOCtrl destructor";
}

void IcpDOCtrl::addSwitchToList(Switch** ptr, int switchesCnt){
    // m_switches.append(QSharedPointer<Switch>(ptr));
    m_switches = ptr;
    m_switchesCnt = switchesCnt;
}

int IcpDOCtrl::initUSBDO(){
    // linux base
    int res;
	int DeviceID = USB2045;
	BYTE BoardID = 0x1;
	BYTE module_name[15], total_do;

    res = USBIO_OpenDevice(DeviceID, BoardID, &DevNum);

    if (res){
        qDebug() << QString("OpenDevice error Erro : 0x%1\r").arg(res);
        res = USBIO_CloseDevice(DevNum);
        return -1;
    }
    // USBIO_ModuleName(DevNum, module_name);
	USBIO_GetDOTotal(DevNum, &total_do); // DI?

    m_total_do = total_do;

    qDebug() << "Switches count = " << m_switchesCnt;
    qDebug() << "total_do =  " << m_total_do;
    // windows base
    // int iErrCode;
    // WORD wFWVer;
    // BYTE bySupIOMask, byDeviceNickName[32], byDeviceSN[32];

    // USB_DO = CreateInstance();

    // if(ERR_NO_ERR != (iErrCode = OpenDevice(USB_DO, USB2045, 1))){
    //     char szMessage[10];
    //     qDebug() << QString("OpenDevice error [%1]").arg(iErrCode);
    //     CloseDevice(USB_DO);
    //     USB_DO = nullptr;
    //     return -1;
    // }

    // GetSupportIOMask(USB_DO, &bySupIOMask);
    // GetDeviceNickName(USB_DO, byDeviceNickName);
    // GetDeviceSN(USB_DO, byDeviceSN);
    // GetDOTotal(USB_DO, &m_byDOTotal);
    return 0;
}

void IcpDOCtrl::startTest(){
    DWORD DOValue = 0xf; // or [2]?
    auto res = USBIO_DO_ReadValue(DevNum, &DOValue);
    if (res){
        qDebug() << QString("SetTypeCode error Erro : 0x%1\r").arg(res);
        connectionState = false;
        // emit disconnect state
        return;
    }
    QVector<bool> vector;
    for(auto i = 0; i < m_total_do; ++i){
        vector.append(DOValue >> i&0x1);
    }
    // could it be a template?
    for(auto i = 0; i < m_switchesCnt; ++i){
        m_switches[i]->setState(vector[i]);
    }
    //windows base
    // BYTE o_byDORead[2];
    // DO_ReadValue(USB_DO, o_byDORead);
    // for(int j = 0; j < 7; ++j){
    //     vector.append(o_byDORead[0]>>j&0x1); // from back
    // }
    // for(int j = 0; j < 2; ++j){
    //     vector.append(o_byDORead[1]>>j&0x1); // from back
    // }
    // auto it_begin = m_switches.begin();
    // for(auto i = 0; i < vector.size(); ++i){
    //     m_switches[i]->setState(vector[i]);
    // }
}

void IcpDOCtrl::updateSwitchState(){
    DWORD DOValue = 0; // or [2]?
    // but m_switchesCnt less or equal 8
    for(auto i = 0; i < m_switchesCnt; ++i){
        if(m_switches[i]->getState())
            DOValue|=1u<<i;
    }
    auto res = USBIO_DO_WriteValue(DevNum, &DOValue);
    if (res){
        qDebug() << QString("SetTypeCode error Erro : 0x%1\r").arg(res);
        connectionState = false;
        // emit disconnect state
        return;
    }
}