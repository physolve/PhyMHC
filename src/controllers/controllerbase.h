#pragma once

// #include <windows.h>
// #include "../lib/USBIO_CSWrapper.h"
// #include "../lib/ICPDAS_USBIO.h"
// #pragma comment(lib, "ICPDAS_USBIO.lib")
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
    void startTest() override;
signals:
    void valueChanged(); //?

protected slots:
    void processEvents(); //?

private:
    QTimer* m_timer;
    QElapsedTimer m_programmTime;

    // ICPDAS_USBIO* USB_AI; // each device
    bool USB_AI;
    int DevNum;

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
    void addSwitchToList(Switch** ptr);
    int initUSBDO();
    void startTest() override;
    // void setSwitchList(const QList<Switch>& switches);
    // QList<Switch> getSwitchList() const;
    void testInitialValue();
private:
    // ICPDAS_USBIO* USB_DO; // each device
    bool USB_DO;
    int DevNum;
    // QList<QSharedPointer<Switch>> m_switches;
    Switch** m_switches;
    // fans // port 1, 0?
    // flow valves // port 2, 0?
    // heaters // port 1, 0?
};
