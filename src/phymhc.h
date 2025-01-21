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

public:
    PhyMHC(int &argc, char **argvm);
    ~PhyMHC();
    Q_INVOKABLE void getCustomPlotPtr(CustomPlotItem* testAxisTag);
    Q_INVOKABLE void manualTestControllerStart();
private:
    void initGUI();
    void initTestData();
    void initTestController();
    
    ScriptBase m_scriptDefault;
    QQmlApplicationEngine m_engine;
    CustomPlotItem* m_testAxisTag;

    // create objects for controllers. DO valves, fans, flow, heaters. AI pressure, thermocouples, flow 

    QSharedPointer<ControllerData> time;
    QSharedPointer<ControllerData> upstream;
    QSharedPointer<ControllerData> downstream;

    TestController* testController;
};