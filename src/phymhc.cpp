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
    // QList<QSharedPointer<ControllerData>> testStorage = ;
    testController.setTimeData(&time);
    testController.setUpstreamData(&upstream);
    testController.setDownstreamData(&downstream);

    analogController.setData(&timeAnalog, DataType::TYPE_time);
    analogController.setData(&tcUp, DataType::TYPE_tcUp);
    analogController.setData(&prUp, DataType::TYPE_prUp);
    analogController.setData(&flUp, DataType::TYPE_flUp);
    analogController.setData(&tcDw, DataType::TYPE_tcDw);
    analogController.setData(&prDw, DataType::TYPE_prDw);
    analogController.setData(&flDw, DataType::TYPE_flDw);
    analogController.initUSBAI();
    emit analogConnectedChanged();
    // QList<Switch*> swtiches = {&vUp,&vDw,&vSu,&coolUp,&coolDw,&hUp,&hDw};
    Switch *switchList[9] = {&vUp,&vDw,&vSu,&coolUp,&coolDw,&hUp,&hDw,&vflUp,&vflDw};
    digitalController.addSwitchToList(switchList);
    digitalController.initUSBDO();
    emit digitalConnectedChanged();

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

void PhyMHC::manualTestControllerStart(){
    testController.startTest();
}

void PhyMHC::doInitialTestValue(){
    digitalController.testInitialValue();
    // show it on mnemoscheme
    
}