#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>

#include "scriptbase.h"
#include "chart/customplotitem.h"
#include "controllers/testcontroller.h"
#include "controllers/controllerbase.h"

class PhyMHC : public QApplication
{
    Q_OBJECT
    Q_PROPERTY (bool analogConnected READ getAnalogConnected NOTIFY analogConnectedChanged)
    Q_PROPERTY (bool digitalConnected READ getDigitalConnected NOTIFY digitalConnectedChanged)

public:
    PhyMHC(int &argc, char **argvm);
    ~PhyMHC();
    Q_INVOKABLE void getCustomPlotPtr(CustomPlotItem* testAxisTag);
    Q_INVOKABLE void manualTestControllerStart();
private:
    void initGUI();
    void initTestData();
    void initTestController();

    void initAnalogData();
    void initDigitalData();
    bool getDigitalConnected() const;
    bool getAnalogConnected() const;
signals:
    void analogConnectedChanged();
    void digitalConnectedChanged();

private:
    
    ScriptBase m_scriptDefault;
    QQmlApplicationEngine m_engine;
    CustomPlotItem* m_testAxisTag;

    // create objects for controllers. DO valves, fans, flow, heaters. AI pressure, thermocouples, flow 
    TestController* testController;

    QSharedPointer<ControllerData> time;
    QSharedPointer<ControllerData> upstream;
    QSharedPointer<ControllerData> downstream;

    IcpAICtrl* analogController;

    QSharedPointer<ControllerData> timeAnalog; 
    QSharedPointer<ControllerData> tcUp; // ch0
    QSharedPointer<ControllerData> prUp; // ch1
    QSharedPointer<ControllerData> flUp; // ch2

    QSharedPointer<ControllerData> tcDw; // ch3
    QSharedPointer<ControllerData> prDw; // ch4
    QSharedPointer<ControllerData> flDw; // ch5

    IcpDOCtrl* digitalController;

    Switch vUp; // port 0, ch0
    Switch vDw; // port 0, ch1
    Switch vSu; // port 0, ch2
    Switch coolUp; // port 0, ch3
    Switch coolDw; // port 0, ch4
    Switch hUp; // port 0, ch5
    Switch hDw; // port 0, ch6 
    
    Switch vflUp; // port 1, ch0
    Switch vflDw; // port 2, ch1

};