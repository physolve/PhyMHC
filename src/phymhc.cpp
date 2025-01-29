#include "phymhc.h"

#include <QDebug>
#include <QQmlContext>
#include <QQuickStyle>
#include "chart/customplotitem.h"

PhyMHC::PhyMHC(int &argc, char **argv): 
    QApplication(argc, argv), m_scriptDefault(), m_testAxisTag(nullptr),
    time("time"), upstream("upstream"), downstream("downstream"),
    timeAnalog("time"), tcUp("Thermocoulpe upstream"), prUp("Pressure upstream"),
    flUp("Flow upstream"), tcDw("Thermocoulpe downstream"), prDw("Pressure downstream"), flDw("Flow downstream")
{
    initDigitalData();
    initTestController();
    
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
    m_engine.load(url);
}

void PhyMHC::initDigitalData(){
    vUp.m_name = "Valve Upstream"; // port 0, ch0
    vDw.m_name = "Valve Downstream"; // port 0, ch1
    vSu.m_name = "Valve Supply"; // port 0, ch2
    coolUp.m_name = "Cooler Upstream"; // port 0, ch3
    coolDw.m_name = "Cooler Downstream"; // port 0, ch4
    hUp.m_name = "Heater Upstream"; // port 0, ch5
    hDw.m_name = "Heater Downstream"; // port 0, ch6 
    vflUp.m_name = "Valve Flow Upstream"; // port 1, ch0
    vflDw.m_name = "Valve Flow Downstream"; // port 2, ch1
}

void PhyMHC::initTestController(){
    testController.setTimeData(&time);
    testController.setUpstreamData(&upstream);
    testController.setDownstreamData(&downstream);
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
}

void PhyMHC::icpDoController(){
    // QList<Switch*> swtiches = {&vUp,&vDw,&vSu,&coolUp,&coolDw,&hUp,&hDw};
    Switch *switchList[8] = {&vUp,&vDw,&vSu,&coolUp,&coolDw,&hUp,&hDw,&vVa};
    digitalController.addSwitchToList(switchList, 8);
    digitalController.initUSBDO();
    emit digitalConnectedChanged();
    if(digitalController.isConnected()) digitalController.startTest(); 
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
    m_testAxisTag->setDataPointers(&time, DataType::TYPE_time);
    m_testAxisTag->setDataPointers(&upstream, DataType::TYPE_prUp);
    m_testAxisTag->setDataPointers(&downstream, DataType::TYPE_prDw);
    // Switch *test = new Switch;
    m_testAxisTag->initCustomPlot();
    connect(&testController, &TestController::valueChanged, m_testAxisTag, &CustomPlotItem::dataUpdated);
}

void PhyMHC::doValveChange(){
    if(digitalController.isConnected())
        digitalController.updateSwitchState();
}

// from script
void PhyMHC::manualTestControllerStart(){
    testController.startTest();
}

void PhyMHC::setVUp(bool state){
    vUp.setState(state);
    // Valve upstream handler
    // vUp.setState( vUpHandle(state) ) 
    emit vUpChanged();
    doValveChange(); // handles + set State to doValveChange return bool!
}
void PhyMHC::setVDw(bool state){
    vDw.setState(state);
    // Valve downstream handler
    // vDw.setState( vDwHandle(state) ) 
    emit vDwChanged();
    doValveChange();
}
void PhyMHC::setVSu(bool state){
    vSu.setState(state);
    // Valve supply handler
    // vSu.setState( vSuHandle(state) ) 
    emit vSuChanged();
    doValveChange();
}
void PhyMHC::setCoolUp(bool state){
    coolUp.setState(state);
    // Cooler upstream manual turn handler
    // coolUp.setState( coolUpHandle(state) ) 
    doValveChange();
    emit coolUpChanged();
}
void PhyMHC::setCoolDw(bool state){
    coolDw.setState(state);
    // Cooler upstream manual turn handler
    // coolDw.setState( coolDwHandle(state) )
    doValveChange(); 
    emit coolDwChanged();
}
void PhyMHC::setHUp(bool state){
    hUp.setState(state);
    // Heater upstream manual turn handler
    // hUp.setState( hUpHandle(state) )
    doValveChange(); 
    emit hUpChanged();
}
void PhyMHC::setHDw(bool state){
    hDw.setState(state);
    // Heater upstream manual turn handler
    // hDw.setState( hDwHandle(state) )
    doValveChange(); 
    emit hDwChanged();
}
void PhyMHC::setVVa(bool state){
    vVa.setState(state);
    // Valve vacuum handler
    // vVa.setState( vVaHandle(state) )
    doValveChange(); 
    emit vVaChanged();
}

bool PhyMHC::getVUp() const{
    return vUp.getState();
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
