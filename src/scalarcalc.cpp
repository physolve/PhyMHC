#include "scalarcalc.h"

ScalarCalc::ScalarCalc(QObject *parent) : QObject(parent), isExposure(false), isAppend(false), isRemove(false) //, clockTime("00:00:00"), scalarStr("0.000"), runCnt(1)
{
    m_currentScalar = 0;
    m_previousFlowAppend = 0;
    m_previousFlowRemove = 0;
    m_previousTime = 0;
    clockTime = "00:00:00";
}

ScalarCalc::~ScalarCalc(){
    qDebug() << "Scalar Calc destructor";
}

void ScalarCalc::updateFromBackend(){
    emit exposureChanged();
    emit appendChanged();
    emit removeChanged();
}

void ScalarCalc::setVolumeValue(double volumeValue){
    setCurrentScalar(volumeValue);
    // update gui also
    emit currentScalarChanged();
}

void ScalarCalc::setExposure(bool state){
    isExposure = state;
    m_timeStart = QTime::currentTime();

    m_previousFlowAppend = 0;
    m_previousFlowRemove = 0;
    m_previousTime = m_time->getCurValue();
    clockTime = "00:00:00";

    if(!isExposure){
        isAppend = false;
        isRemove = false;
        emit appendChanged();
        emit removeChanged();
    }
}

bool ScalarCalc::getExposure() const{
    return isExposure;
}

void ScalarCalc::setAppend(bool state){
    isAppend = state;
    // automatically remove off
    if(isAppend){
        isRemove = false;
        emit removeChanged();
    }
}

bool ScalarCalc::getAppend() const{
    return isAppend;
}

void ScalarCalc::setRemove(bool state){
    isRemove = state;
    // automatically append off
    if(isRemove){
        isAppend = false;
        emit appendChanged();
    }
}

bool ScalarCalc::getRemove() const{
    return isRemove;
}

void ScalarCalc::setCalcData(DataCollection* time, DataCollection* flowFarAppend, DataCollection* flowNearRemove, DataCollection* reactorCharge){
    m_time = time;
    m_flowFarAppend = flowFarAppend;
    m_flowNearRemove = flowNearRemove;
    m_reactorCharge = reactorCharge;
}

void ScalarCalc::setCurrentScalar(double scalar){
    m_currentScalar = scalar;
}

double ScalarCalc::getCurrentScalar() const{
    return m_currentScalar;
}

void ScalarCalc::processCalc(){
    const auto& curTime = m_time->getCurValue();
    if(isAppend){
        const auto& curFlowAppend = m_flowFarAppend->getCurValue();
        calcScalar(m_previousFlowAppend, curFlowAppend, m_previousTime, curTime);
        m_previousFlowAppend = curFlowAppend;
    }
    if(isRemove){
        const auto& curFlowRemove = - m_flowNearRemove->getCurValue(); // negative
        calcScalar(m_previousFlowRemove, curFlowRemove, m_previousTime, curTime);
        m_previousFlowRemove = curFlowRemove;
    }
    m_previousTime = curTime;
    m_reactorCharge->addPoint(m_currentScalar);
    emit currentScalarChanged();
    m_duration = m_timeStart.secsTo(QTime::currentTime());
    clockTime = QTime(0,0,0,0).addSecs(m_duration).toString("hh:mm:ss");
    // emit clockTimeChanged();
}

void ScalarCalc::calcScalar(double y0, double y1, qreal x0, qreal x1){
    double scalar = (y0+y1)/2.0*(x1-x0)/60.0;
    // it might be based on m_reactorCharge
    this->m_currentScalar += scalar; // litres
    // scalarStr = QString::number(this->m_currentScalar, 'g', 5);
    // emit scalarStrChanged();
}

QString ScalarCalc::getClockTime() const{
    return clockTime;
}

int ScalarCalc::getSecondsTime() const{
    return m_duration;
}