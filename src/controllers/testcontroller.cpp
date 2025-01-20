#include "testcontroller.h"

TestController::TestController(QList<QSharedPointer<ControllerData>> dataStorage, QObject *parent) : 
    QObject(parent), m_timer(new QTimer)
{
    connect(m_timer, &QTimer::timeout, this, &TestController::processEvents);
    time = dataStorage[0];
    upstream = dataStorage[1];
    downstream = dataStorage[2];
}

TestController::~TestController(){
    if(m_timer->isActive()) m_timer->stop();
}

void TestController::startTest(){
    m_programmTime.start();
    m_timer->start(33);
}

void TestController::processEvents(){
    const auto &c_time = m_programmTime.elapsed()/1000.0;
    time->addPoint(c_time);
    upstream->addPoint(qSin(c_time/50.0)+qSin(c_time/0.3843)*0.25);
    downstream->addPoint(qCos(c_time/50.0)+qSin(c_time/50.0/0.4364)*0.15);
    emit valueChanged();
}