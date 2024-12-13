#include "phymhc.h"

#include <QDebug>
#include <QQmlContext>
#include <QQuickStyle>
// #include "CustomPlotItem.h"

PhyMHC::PhyMHC(int &argc, char **argv): 
    QApplication(argc, argv), m_scriptDefault()
{
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
    
    // qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    m_engine.rootContext()->setContextProperty("scriptDefault", &m_scriptDefault);
    m_engine.rootContext()->setContextProperty("backend", this);
    m_engine.load(url);
}