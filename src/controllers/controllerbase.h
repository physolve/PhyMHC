#pragma once

#include <windows.h>
#include "../lib/USBIO_CSWrapper.h"
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
//     virtual void startTest();
// signals:
//     virtual void valueChanged(); //?

// protected slots:
//     virtual void processEvents(); //?

protected:
    QElapsedTimer m_programmTime;
    QTimer* m_timer;

private:
    ICPDAS_USBIO* USBIO_CS; // each device
};

class IcpAICtrl : public ControllerBase{
    Q_OBJECT // ?

public:
    IcpAICtrl(QList<QSharedPointer<ControllerData>> dataStorage, QObject *parent = nullptr);
    virtual ~IcpAICtrl();
//     void startTest() override;
// signals:
//     void valueChanged() override;

// private slots:
//     void processEvents() override;

};