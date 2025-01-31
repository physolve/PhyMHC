#pragma once

#include <windows.h>
// #include "../icp/ICPDAS_USBIO.h"
#include "../icp/USBIO_CSWrapper.h"
#pragma comment(lib, "ICPDAS_USBIO.lib")
#include "../datacollection.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QSharedPointer>

class ControllerBase : public QObject
{
    Q_OBJECT
    
public:
    ControllerBase(QObject *parent = nullptr);
    virtual ~ControllerBase();
    virtual void startTest();
    QString name;
    bool isConnected() const;
protected:
    bool connectionState;
};

class IcpAICtrl : public ControllerBase{
    Q_OBJECT // ?

public:
    IcpAICtrl(QObject *parent = nullptr);
    virtual ~IcpAICtrl();
    int initUSBAI();
    void setData(ControllerData* ptr, DataType type);
    void tempFunctionToSetChannelsType();
    void setTypeCodeToChannels();
    void startTest() override;
signals:
    void valueChanged(); //?

protected slots:
    void processEvents(); //?

private:
    QTimer* m_timer;
    QElapsedTimer m_programmTime;

    ICPDAS_USBIO* USB_AI; // each device
    // bool USB_AI;
    // int DevNum;

    ControllerData* time;
    ControllerData* tcUp;
    ControllerData* prUp;
    ControllerData* flUp;
    ControllerData* tcDw;
    ControllerData* prDw;
    ControllerData* flDw;
};

class IcpDOCtrl : public ControllerBase{
    Q_OBJECT

public:
    IcpDOCtrl(QObject *parent = nullptr);
    virtual ~IcpDOCtrl();
    void addSwitchToList(Switch ptr[], int switchesCnt);
    int initUSBDO();
    void startTest() override;
    bool updateSwitchState();

private:
    ICPDAS_USBIO* USB_DO; // each device
    // bool USB_DO;
    // int DevNum;
    uint16_t m_total_do;
    // QList<QSharedPointer<Switch>> m_switches;
    int m_switchesCnt;
    Switch* m_switches[8];
    // fans // port 1, 0?
    // flow valves // port 2, 0?
    // heaters // port 1, 0?
};
