#include "testcontroller.h"

TestController::TestController(QObject *parent) : 
    QObject(parent), m_timer(new QTimer)
{
    connect(m_timer, &QTimer::timeout, this, &TestController::processEvents);
}

TestController::~TestController(){
    qDebug() << "test controller destructor";
    if(m_timer->isActive()) m_timer->stop();
}

void TestController::setTimeData(ControllerData* ptr){
    time = QSharedPointer<ControllerData>(ptr);
}

void TestController::setUpstreamData(ControllerData* ptr){
    upstream = QSharedPointer<ControllerData>(ptr);
}

void TestController::setDownstreamData(ControllerData* ptr){
    downstream = QSharedPointer<ControllerData>(ptr);
}

void TestController::startTest(){
    m_programmTime.start();
    m_timer->start(250);
}

void TestController::processEvents(){
    const auto &c_time = m_programmTime.elapsed()/1000.0;
    time->addPoint(c_time);
    upstream->addPoint(qSin(c_time/50.0)+qSin(c_time/0.3843)*0.25);
    downstream->addPoint(qCos(c_time/50.0)+qSin(c_time/50.0/0.4364)*0.15);
    emit valueChanged();
}