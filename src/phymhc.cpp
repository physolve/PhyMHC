#include "phymhc.h"

#include <QDebug>
#include <QQmlContext>
#include <QQuickStyle>
#include "chart/customplotitem.h"

PhyMHC::PhyMHC(int &argc, char **argv): 
    QApplication(argc, argv), m_scriptDefault(), m_testAxisTag(nullptr),
    // time("time"), upstream("upstream"), downstream("downstream"),
    timeAnalog("time"), tcUp("Thermocoulpe upstream"), prUp("Pressure upstream"),
    flUp("Flow upstream"), tcDw("Thermocoulpe downstream"), prDw("Pressure downstream"), flDw("Flow downstream"),
    reactorUps("Reactor upstream"), reactorDws("Reactor downstream")
{
    initDigitalData();
    initTestController();
    icpAiController();
    icpDoController();
    initScalarCalc();
    initRunConfig();
    initLogData();
    initGUI();
}

PhyMHC::~PhyMHC(){
    m_engine.clearComponentCache();
    // qDebug() << m_testAxisTag;
    delete m_testAxisTag;
    // m_testAxisTag = nullptr;
}

void PhyMHC::initGUI(){
    QQuickStyle::setStyle("Material");
    QString applicationName = "PhyMHC";
    
    m_engine.addImportPath(":/");
    const QUrl url(QString("qrc:/%1/qml/main.qml").arg(applicationName));
    QObject::connect(
                &m_engine, &QQmlApplicationEngine::objectCreated, this,
                [url](QObject *obj, const QUrl &objUrl) {
                    if(!obj && url == objUrl) QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    
    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    m_engine.rootContext()->setContextProperty("scriptDefault", &m_scriptDefault);
    m_engine.rootContext()->setContextProperty("backend", this);
    m_engine.rootContext()->setContextProperty("scalarUpstream", &flowToVolumeUpstream);
    m_engine.rootContext()->setContextProperty("scalarDownstream", &flowToVolumeDownstream);
    m_engine.rootContext()->setContextProperty("runConfig", &runConfig);
    m_engine.load(url);
}

void PhyMHC::initDigitalData(){
    tcUp.setCoeffs(1.0, 0.0);
    prUp.setCoeffs(15.618, -14.977);
    flUp.setCoeffs(10.0, 0.0);
    tcDw.setCoeffs(1.0, 0.0);
    prDw.setCoeffs(15.618, -14.977);
    flDw.setCoeffs(10.0, 0.0);

    vUp.m_name = "Valve Upstream"; // port 0, ch0
    vDw.m_name = "Valve Downstream"; // port 0, ch1
    vVa.m_name = "Valve Vacuum"; // port 0, ch2
    coolUp.m_name = "Cooler Upstream"; // port 0, ch3
    coolDw.m_name = "Cooler Downstream"; // port 0, ch4
    hUp.m_name = "Heater Upstream"; // port 0, ch5
    hDw.m_name = "Heater Downstream"; // port 0, ch6 
    vSu.m_name = "skip"; // port 0, ch7

    // vflUp.m_name = "Valve Flow Upstream"; // port 1, ch0
    // vflDw.m_name = "Valve Flow Downstream"; // port 2, ch1

    m_guiVals.m_temperatureUpstream = 0.0;
    m_guiVals.m_pressureUpstream = 0.0;
    m_guiVals.m_flowUpstream = 0.0;
    m_guiVals.m_flowUpstreamMoles = 0.000001;
    m_guiVals.m_temperatureDownstream = 0.0;
    m_guiVals.m_pressureDownstream = 0.0;
    m_guiVals.m_flowDownstream = 0.0;
    m_guiVals.m_flowDownstreamMoles = 0.000001;
}

void PhyMHC::initTestController(){
    testController.setTimeData(&timeAnalog);
    testController.setUpstreamData(&flUp);
    testController.setDownstreamData(&flDw);
}

void PhyMHC::icpAiController(){
    analogController.setData(&timeAnalog, DataType::TYPE_time);
    analogController.setData(&tcUp, DataType::TYPE_tcUp);
    analogController.setData(&prUp, DataType::TYPE_prUp);
    analogController.setData(&flUp, DataType::TYPE_flUp);
    analogController.setData(&tcDw, DataType::TYPE_tcDw);
    analogController.setData(&prDw, DataType::TYPE_prDw);
    analogController.setData(&flDw, DataType::TYPE_flDw);
    analogController.initUSBAI();
    emit analogConnectedChanged();

    connect(&analogController, &IcpAICtrl::valueChanged, this, &PhyMHC::guiValsUpdate);
    // if ok start test
    if(analogController.isConnected()){
        analogController.startTest();
    }
}

void PhyMHC::icpDoController(){
    Switch *switchList[8] = {&vUp, &vDw, &vVa, &coolUp, &coolDw, &hUp, &hDw, &vSu};
    digitalController.addSwitchToList(*switchList, 8);
    digitalController.initUSBDO();
    emit digitalConnectedChanged();
    if(digitalController.isConnected()){
        digitalController.startTest();
        // doSwitchChange();
        emit vUpChanged();
        emit vDwChanged();
        emit vSuChanged();
        emit coolUpChanged();
        emit coolDwChanged();
        emit hUpChanged();
        emit hDwChanged();
        emit vVaChanged();
    }
}

void PhyMHC::initScalarCalc(){
    flowToVolumeUpstream.setCalcData(&timeAnalog, &flUp, &flDw, &reactorUps);
    flowToVolumeDownstream.setCalcData(&timeAnalog, &flDw, &flUp, &reactorDws);
    // connect(&flowToVolumeUpstream, &ScalarCalc::valueChanged, this, &PhyMHC::guiValsUpdate); later
}

void PhyMHC::initRunConfig(){
    runConfig.setData(&tcUp, LogType::LOG_tcUp);
    runConfig.setData(&prUp, LogType::LOG_prUp);
    runConfig.setData(&flUp, LogType::LOG_flUp);
    runConfig.setData(&tcDw, LogType::LOG_tcDw);
    runConfig.setData(&prDw, LogType::LOG_prDw);
    runConfig.setData(&flDw, LogType::LOG_flDw);
    runConfig.setData(&reactorUps, LogType::LOG_reactorUps);
    runConfig.setData(&reactorDws, LogType::LOG_reactorDws);
    m_runParams = runConfig.getRunParameters();
    // m_runParams.initialLitresFrom = flowToVolumeUpstream.getCurrentScalar();
    // m_runParams.initialLitresTo = flowToVolumeDownstream.getCurrentScalar();
    //m_runParams.clockTime = flowToVolumeUpstream.getClockTime(); // ?
    runConfig.updateRunParameters(m_runParams);
}

void PhyMHC::initLogData(){
    logData.setData(&tcUp, LogType::LOG_tcUp);
    logData.setData(&prUp, LogType::LOG_prUp);
    logData.setData(&flUp, LogType::LOG_flUp);
    logData.setData(&tcDw, LogType::LOG_tcDw);
    logData.setData(&prDw, LogType::LOG_prDw);
    logData.setData(&flDw, LogType::LOG_flDw);
    logData.setData(&reactorUps, LogType::LOG_reactorUps);
    logData.setData(&reactorDws, LogType::LOG_reactorDws);
    logData.startLog();
}

bool PhyMHC::getDigitalConnected() const{
    return digitalController.isConnected();
}

bool PhyMHC::getAnalogConnected() const{
    // const auto& isCon = analogController.isConnected(); 
    return analogController.isConnected();
}

void PhyMHC::getCustomPlotPtr(CustomPlotItem* testAxisTag){
    m_testAxisTag = testAxisTag;
    DataCollection* chartPtrs[3] = {&timeAnalog, &flUp, &flDw};
    m_testAxisTag->setDataPointers(chartPtrs, 3);
    
    m_testAxisTag->initCustomPlot();
    connect(&testController, &TestController::valueChanged, m_testAxisTag, &CustomPlotItem::dataUpdated);
    connect(&analogController, &IcpAICtrl::valueChanged, m_testAxisTag, &CustomPlotItem::dataUpdated);
}

bool PhyMHC::doSwitchChange(){
    if(!digitalController.isConnected())
        return false;
    return digitalController.updateSwitchState();
}

bool PhyMHC::passRunParametersGui(const QVariantList &params){
    if(params.isEmpty() || params.count() != 12){
        qDebug() << "Passed wrong paramters";
        return false;
    }
    m_runParams.runName = params.at(0).toString();
    m_runParams.releaseFrom = params.at(1).toString();
    m_runParams.endLitresFrom = m_runParams.initialLitresFrom = params.at(2).toDouble();
    m_runParams.loadTo = params.at(3).toString();
    m_runParams.endLitresTo = m_runParams.initialLitresTo = params.at(4).toDouble();
    m_runParams.upstreamToDownstream = params.at(5).toBool();
    m_runParams.downstreamToUpstream = params.at(6).toBool();
    m_runParams.upstreamToAir = params.at(7).toBool();
    m_runParams.downstreamToAir = params.at(8).toBool();
    m_runParams.supplyToUpstream = params.at(9).toBool();
    m_runParams.supplyToDownstream = params.at(10).toBool();
    m_runParams.logHeaderComment = params.at(11).toString();
    return true;
}

void PhyMHC::guiValsUpdate(){
    m_guiVals.m_flowUpstream = flUp.getCurValue();
    m_guiVals.m_flowDownstream = flDw.getCurValue();
    m_guiVals.m_temperatureUpstream = tcUp.getCurValue();
    m_guiVals.m_temperatureDownstream = tcDw.getCurValue();
    m_guiVals.m_pressureUpstream = prUp.getCurValue();
    m_guiVals.m_pressureDownstream = prDw.getCurValue();
    emit guiValsChanged();

    // also for now update flow here, later make another connection
    if(flowToVolumeUpstream.getExposure()){
        flowToVolumeUpstream.processCalc();
    }
    if(flowToVolumeDownstream.getExposure()){
        flowToVolumeDownstream.processCalc();
    }

    //updateRunParams
    // if runConfig to runConfig
    if(runConfig.isRunLog()){
        updateGuiRun();
    }
}

void PhyMHC::updateGuiRun(){  
    if(m_runParams.downstreamToUpstream){
        m_runParams.totalLitresPass = flowToVolumeUpstream.getCurrentScalar()-m_runParams.initialLitresTo;
        m_runParams.endLitresTo = flowToVolumeUpstream.getCurrentScalar();
        m_runParams.endLitresFrom = flowToVolumeDownstream.getCurrentScalar();
        m_runParams.differenseToFrom = (m_runParams.initialLitresFrom-m_runParams.endLitresFrom)-(m_runParams.endLitresTo-m_runParams.initialLitresTo);
        m_runParams.totalTimeSec = flowToVolumeUpstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeUpstream.getClockTime();
    }
    else if(m_runParams.upstreamToDownstream){
        m_runParams.totalLitresPass = flowToVolumeDownstream.getCurrentScalar()-m_runParams.initialLitresTo;
        m_runParams.endLitresTo = flowToVolumeDownstream.getCurrentScalar();
        m_runParams.endLitresFrom = flowToVolumeUpstream.getCurrentScalar();
        m_runParams.differenseToFrom = (m_runParams.initialLitresFrom-m_runParams.endLitresFrom)-(m_runParams.endLitresTo-m_runParams.initialLitresTo);
        m_runParams.totalTimeSec = flowToVolumeDownstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeDownstream.getClockTime();
    }
    else if(m_runParams.upstreamToAir){
        m_runParams.totalLitresPass = m_runParams.initialLitresFrom-flowToVolumeUpstream.getCurrentScalar();
        m_runParams.endLitresFrom = flowToVolumeUpstream.getCurrentScalar();
        m_runParams.totalTimeSec = flowToVolumeUpstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeUpstream.getClockTime();
    }
    else if(m_runParams.downstreamToAir){
        m_runParams.totalLitresPass = m_runParams.initialLitresFrom-flowToVolumeDownstream.getCurrentScalar();
        m_runParams.endLitresFrom = flowToVolumeDownstream.getCurrentScalar();
        m_runParams.totalTimeSec = flowToVolumeDownstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeDownstream.getClockTime();
    }
    else if(m_runParams.supplyToUpstream){
        m_runParams.totalLitresPass = flowToVolumeUpstream.getCurrentScalar()-m_runParams.initialLitresTo;
        m_runParams.endLitresTo = flowToVolumeUpstream.getCurrentScalar();
        m_runParams.totalTimeSec = flowToVolumeUpstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeUpstream.getClockTime();
    }
    else if(m_runParams.supplyToDownstream){
        m_runParams.totalLitresPass = flowToVolumeDownstream.getCurrentScalar()-m_runParams.initialLitresTo;
        m_runParams.endLitresTo = flowToVolumeDownstream.getCurrentScalar();
        m_runParams.totalTimeSec = flowToVolumeDownstream.getSecondsTime();
        m_runParams.clockTime = flowToVolumeDownstream.getClockTime();
    }
    runConfig.updateRunParameters(m_runParams);
}

guiValues PhyMHC::getGuiVals() const{
    return m_guiVals;
}

void PhyMHC::runFromGui(){
    runConfig.updateRunParameters(m_runParams);
    if(m_runParams.downstreamToUpstream){
        flowToVolumeDownstream.setVolumeValue(m_runParams.initialLitresFrom);
        flowToVolumeUpstream.setVolumeValue(m_runParams.initialLitresTo);
        flowToVolumeDownstream.setExposure(true);
        flowToVolumeUpstream.setExposure(true);

        flowToVolumeDownstream.setRemove(true);
        flowToVolumeUpstream.setRemove(false);

        flowToVolumeDownstream.setAppend(false);
        flowToVolumeUpstream.setAppend(true);

        flowToVolumeDownstream.updateFromBackend();
        flowToVolumeUpstream.updateFromBackend();
    }
    else if(m_runParams.upstreamToDownstream){
        flowToVolumeUpstream.setVolumeValue(m_runParams.initialLitresFrom);
        flowToVolumeDownstream.setVolumeValue(m_runParams.initialLitresTo);
        flowToVolumeUpstream.setExposure(true);
        flowToVolumeDownstream.setExposure(true);

        flowToVolumeUpstream.setRemove(true);
        flowToVolumeDownstream.setRemove(false);

        flowToVolumeUpstream.setAppend(false);
        flowToVolumeDownstream.setAppend(true);

        flowToVolumeUpstream.updateFromBackend();
        flowToVolumeDownstream.updateFromBackend();
    }
    else if(m_runParams.upstreamToAir){
        flowToVolumeUpstream.setVolumeValue(m_runParams.initialLitresFrom);
        flowToVolumeUpstream.setExposure(true);
        flowToVolumeUpstream.setRemove(true);
        flowToVolumeUpstream.setAppend(false);
        flowToVolumeUpstream.updateFromBackend();
    }
    else if(m_runParams.downstreamToAir){
        flowToVolumeDownstream.setVolumeValue(m_runParams.initialLitresFrom);
        flowToVolumeDownstream.setExposure(true);
        flowToVolumeDownstream.setRemove(true);
        flowToVolumeDownstream.setAppend(false);
        flowToVolumeDownstream.updateFromBackend();
    }
    else if(m_runParams.supplyToUpstream){
        flowToVolumeUpstream.setVolumeValue(m_runParams.initialLitresTo);
        flowToVolumeUpstream.setExposure(true);
        flowToVolumeUpstream.setRemove(false);
        flowToVolumeUpstream.setAppend(true);
        flowToVolumeUpstream.updateFromBackend();
    }
    else if(m_runParams.supplyToDownstream){
        flowToVolumeDownstream.setVolumeValue(m_runParams.initialLitresTo);
        flowToVolumeDownstream.setExposure(true);
        flowToVolumeDownstream.setRemove(false);
        flowToVolumeDownstream.setAppend(true);
        flowToVolumeDownstream.updateFromBackend();
    }
    else{
        qDebug() << "Total error";
        return;
    }
    
    runConfig.logRunCreation();
    runConfig.startRun();
    emit actualRunChanged();
    emit actualReadingChanged();
}

bool PhyMHC::getActualRun() const{
    return runConfig.isRunLog();
}

bool PhyMHC::getActualReading() const{
    return runConfig.isRunLog()&&(flowToVolumeUpstream.getExposure()||flowToVolumeDownstream.getExposure());
}

void PhyMHC::stopFromGui(){
    runConfig.stopRun();
    runConfig.updateRunParameters(m_runParams);
    runConfig.insertTotalLitres(); // log shit
    emit actualRunChanged();
    emit actualReadingChanged();
    if(flowToVolumeUpstream.getExposure()){
        flowToVolumeUpstream.setExposure(false);
        flowToVolumeUpstream.updateFromBackend();
    }
    if(flowToVolumeDownstream.getExposure()){
        flowToVolumeDownstream.setExposure(false);
        flowToVolumeDownstream.updateFromBackend();
    }
    // clear from here
    backup_runParams = m_runParams;
    runConfig.clearRunParameters();
    m_runParams = runConfig.getRunParameters();
    runConfig.formFileName();
    // proceed to clear
}

// from script
void PhyMHC::manualTestControllerStart(){
    testController.startTest();
}

void PhyMHC::setVUp(bool state){
    // Valve upstream handler
    if(vUp.getState() == state)
        return;
    vUp.setState(state);
    // vUp.setState( vUpHandle(state) ) // handle undo state
    if(!doSwitchChange()) // undo state
        vUp.setState(!state); // handles + set State to doSwitchChange return bool!
    emit vUpChanged();
}
void PhyMHC::setVDw(bool state){
    // Valve downstream handler
    if(vDw.getState() == state)
        return;
    vDw.setState(state);
    // vDw.setState( vDwHandle(state) ) 
    if(!doSwitchChange()) // undo state
        vDw.setState(!state);
    emit vDwChanged();
}
void PhyMHC::setVSu(bool state){
    // Valve supply handler
    if(vSu.getState() == state)
        return;
    vSu.setState(state);
    // vSu.setState( vSuHandle(state) ) 
    if(!doSwitchChange()) // undo state
        vSu.setState(!state);
    emit vSuChanged();
}
void PhyMHC::setCoolUp(bool state){
    // Cooler upstream manual turn handler
    if(coolUp.getState() == state)
        return;
    coolUp.setState(state);
    // coolUp.setState( coolUpHandle(state) )
    if(!doSwitchChange()) // undo state
        coolUp.setState(!state); 
    emit coolUpChanged();
}
void PhyMHC::setCoolDw(bool state){
    // Cooler upstream manual turn handler
    if(coolDw.getState() == state)
        return;
    coolDw.setState(state);
    // coolDw.setState( coolDwHandle(state) )
    if(!doSwitchChange()) // undo state
        coolDw.setState(!state); 
    emit coolDwChanged();
}
void PhyMHC::setHUp(bool state){
    // Heater upstream manual turn handler
    if(hUp.getState() == state)
        return;
    hUp.setState(state);
    // hUp.setState( hUpHandle(state) )
    if(!doSwitchChange()) // undo state
        hUp.setState(!state); 
    emit hUpChanged();
}
void PhyMHC::setHDw(bool state){
    // Heater upstream manual turn handler
    if(hDw.getState() == state)
        return;
    hDw.setState(state);
    // hDw.setState( hDwHandle(state) )
    if(!doSwitchChange()) // undo state
        hDw.setState(!state);
    emit hDwChanged();
}
void PhyMHC::setVVa(bool state){
    // Valve vacuum handler
    if(vVa.getState() == state)
        return;
    vVa.setState(state);
    // vVa.setState( vVaHandle(state) )
    if(!doSwitchChange()) // undo state
        vVa.setState(!state);
    emit vVaChanged();
}

bool PhyMHC::getVUp() const{
    return vUp.getState();;
}
bool PhyMHC::getVDw() const{
    return vDw.getState();
}
bool PhyMHC::getVSu() const{
    return vSu.getState();
}
bool PhyMHC::getCoolUp() const{
    return coolUp.getState();
}
bool PhyMHC::getCoolDw() const{
    return coolDw.getState();
}
bool PhyMHC::getHUp() const{
    return hUp.getState();
}
bool PhyMHC::getHDw() const{
    return hDw.getState();
}
bool PhyMHC::getVVa() const{
    return vVa.getState();
}
