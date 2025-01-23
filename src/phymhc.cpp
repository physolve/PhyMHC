#include "phymhc.h"

#include <QDebug>
#include <QQmlContext>
#include <QQuickStyle>
#include "chart/customplotitem.h"

PhyMHC::PhyMHC(int &argc, char **argv): 
    QApplication(argc, argv), m_scriptDefault(), testController(nullptr)
{
    initTestData();
    initTestController();
    initGUI();
}

PhyMHC::~PhyMHC(){
    m_engine.clearComponentCache();
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

void PhyMHC::initTestData(){
    time = QSharedPointer<ControllerData>::create("timeData"); // as base class ok?
    upstream = QSharedPointer<ControllerData>::create("upstream");
    downstream = QSharedPointer<ControllerData>::create("downstream");
}

void PhyMHC::initAnalogData(){
    timeAnalog = QSharedPointer<ControllerData>::create("timeAnalog");
    tcUp = QSharedPointer<ControllerData>::create("tcUp");
    prUp = QSharedPointer<ControllerData>::create("prUp");
    flUp = QSharedPointer<ControllerData>::create("flUp");
    tcDw = QSharedPointer<ControllerData>::create("tcDw");
    prDw = QSharedPointer<ControllerData>::create("prDw");
    flDw = QSharedPointer<ControllerData>::create("flDw");
}

void PhyMHC::initDigitalData(){
    digitalController = new IcpDOCtrl({vUp, vDw, vSu, coolUp, coolDw, hUp, hDw, vflUp, vflDw});
    digitalController->initUSBDO();
    digitalController->startTest();

    emit digitalConnectedChanged();
}

void PhyMHC::initTestController(){
    QList<QSharedPointer<ControllerData>> dataStorage = {time, upstream, downstream};
    testController = new TestController(dataStorage);

    QList<QSharedPointer<ControllerData>> dataStorage = {timeAnalog, tcUp, prUp, flUp, tcDw, prDw, flDw};
    analogController = new IcpAICtrl(dataStorage);
    analogController->initUSBAI();
    emit analogConnectedChanged();


}

bool PhyMHC::getDigitalConnected() const{
    return digitalController->isConnected();
}

bool PhyMHC::getAnalogConnected() const{
    return analogController->isConnected();
}


void PhyMHC::getCustomPlotPtr(CustomPlotItem* testAxisTag){
    m_testAxisTag = testAxisTag;
    m_testAxisTag->initCustomPlot();
    m_testAxisTag->setDataPointers(time, {upstream, downstream});
    connect(testController, &TestController::valueChanged, m_testAxisTag, &CustomPlotItem::dataUpdated);
}

void PhyMHC::manualTestControllerStart(){
    testController->startTest();
}