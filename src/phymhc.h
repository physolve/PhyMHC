#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>

#include "scriptbase.h"
#include "chart/customplotitem.h"
#include "controllers/testcontroller.h"
#include "controllers/controllerbase.h"
#include "scalarcalc.h"
#include "logdatabase.h"

class PhyMHC : public QApplication
{
    Q_OBJECT
    Q_PROPERTY (bool analogConnected READ getAnalogConnected NOTIFY analogConnectedChanged)
    Q_PROPERTY (bool digitalConnected READ getDigitalConnected NOTIFY digitalConnectedChanged)

    Q_PROPERTY (guiValues guiVals READ getGuiVals NOTIFY guiValsChanged) //WRITE setExpTimingStruct 

    // each bool property to each class (valves, heater, cooler, flow)
    Q_PROPERTY (bool vUpState READ getVUp WRITE setVUp NOTIFY vUpChanged)
    Q_PROPERTY (bool vDwState READ getVDw WRITE setVDw NOTIFY vDwChanged)
    Q_PROPERTY (bool vVaState READ getVVa WRITE setVVa NOTIFY vVaChanged)
    Q_PROPERTY (bool vSuState READ getVSu WRITE setVSu NOTIFY vSuChanged)

    Q_PROPERTY (bool coolUpState READ getCoolUp WRITE setCoolUp NOTIFY coolUpChanged)
    Q_PROPERTY (bool coolDwState READ getCoolDw WRITE setCoolDw NOTIFY coolDwChanged)
    Q_PROPERTY (bool hUpState READ getHUp WRITE setHUp NOTIFY hUpChanged)
    Q_PROPERTY (bool hDwState READ getHDw WRITE setHDw NOTIFY hDwChanged)

public:
    PhyMHC(int &argc, char **argvm);
    ~PhyMHC();
    Q_INVOKABLE void getCustomPlotPtr(CustomPlotItem* testAxisTag);
    Q_INVOKABLE void manualTestControllerStart();
private:
    void initGUI();
    void initDigitalData();

    void initTestController();
    void icpAiController();
    void icpDoController();
    void initScalarCalc();
    void initLogData();

    bool getDigitalConnected() const;
    bool getAnalogConnected() const;

    bool doSwitchChange();

    void setVUp(bool state);
    void setVDw(bool state);
    void setVVa(bool state);
    void setCoolUp(bool state);
    void setCoolDw(bool state);
    void setHUp(bool state);
    void setHDw(bool state);
    void setVSu(bool state);

    bool getVUp() const;
    bool getVDw() const;
    bool getVVa() const;
    bool getCoolUp() const;
    bool getCoolDw() const;
    bool getHUp() const;
    bool getHDw() const;
    bool getVSu() const;

signals:
    void analogConnectedChanged();
    void digitalConnectedChanged();

    void guiValsChanged();

    void vUpChanged();
    void vDwChanged();
    void vVaChanged();
    void coolUpChanged();
    void coolDwChanged();
    void hUpChanged();
    void hDwChanged();
    void vSuChanged();

private slots:
    void guiValsUpdate();

private:
    
    ScriptBase m_scriptDefault;
    QQmlApplicationEngine m_engine;
    

    // create objects for controllers. DO valves, fans, flow, heaters. AI pressure, thermocouples, flow 
    TestController testController;
    // ControllerData time;
    // ControllerData upstream;
    // ControllerData downstream;

    IcpAICtrl analogController;

    ControllerData timeAnalog; 
    ControllerData tcUp; // ch0
    ControllerData prUp; // ch1
    ControllerData flUp; // ch2
    ControllerData tcDw; // ch3
    ControllerData prDw; // ch4
    ControllerData flDw; // ch5

    IcpDOCtrl digitalController;

    Switch vUp; // port 0, ch0
    Switch vDw; // port 0, ch1
    Switch vVa; // port 0, ch2
    Switch coolUp; // port 0, ch3
    Switch coolDw; // port 0, ch4
    Switch hUp; // port 0, ch5
    Switch hDw; // port 0, ch6 
    Switch vSu; // port 0, ch7
    // unused
    // Switch vflUp; // port 1, ch0
    // Switch vflDw; // port 2, ch1

    CustomPlotItem* m_testAxisTag;

    guiValues m_guiVals;
    guiValues getGuiVals() const;

    ExpData reactorUps; // throw out somewhere else, later
    ExpData reactorDws; // throw out somewhere else, later

    ScalarCalc flowToVolumeUpstream;
    ScalarCalc flowToVolumeDownstream;

    LogDataBase logData;
};