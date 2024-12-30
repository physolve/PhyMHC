#include "reactormodel.h"

static const double Rgas = 8.31446;
static const double abscTemp = 273.15;

ReactorModel::ReactorModel(QObject *parent) : QObject(parent), m_time(), volumeReactor(2e5), volumePath(1),
m_incomeFlow(0), m_reactionFlow(0), m_outgoingFlow(0), m_pressureBarStart(1), m_pressureBar(0), m_temperatureStart(27), m_temperature(0)
{
    // basically start it's calucaltion on his own
    // has changing input flow and reaction flow
    // provide local calculation for distributing internal moles across volume to calculate pressure
    connect(&m_timer, &QTimer::timeout, this, &ReactorModel::reactorLoop);
    initializeState();
}

ReactorModel::~ReactorModel(){
    if(m_timer.isActive()) m_timer.stop();
}

double ReactorModel::getVolumeReactor() const{
    return volumeReactor;
}

void ReactorModel::initializeState(){
    // do i know volume

    // i know volume so define m_pressureBarStart
    // then distribute this pressure over all volume
    // find
    m_temperature = m_temperatureStart; 
    m_gasMoles = m_gasMolesStart = barToMoles(m_pressureBarStart);
    m_time.start();
}

double ReactorModel::barToMoles(const double &bar) const{
    const double &pressurePa = bar*1e5;
    const double &tempAbs = m_temperature + abscTemp;
    const double &volumeMCube = volumeReactor*1e-6;
    return (pressurePa*volumeMCube)/(Rgas*tempAbs);
}

double ReactorModel::molesToBar(const double &moles) const{
    const double &tempAbs = m_temperature + abscTemp;
    const double &volumeMCube = volumeReactor*1e-6;
    return (moles*Rgas*tempAbs)/volumeMCube;
}

void ReactorModel::incomeMoleFlow(double moles){
    m_incomeFlow = moles; 
}

void ReactorModel::reactionFlow(bool on){
    m_reactionFlow = on ? -1 : 0;
}

void ReactorModel::outgoingFlow(double moles){
    m_outgoingFlow = moles;
}

void ReactorModel::setCurrentTemp(const double &temp){
    m_temperature = temp;
}

void ReactorModel::startReactionLoop(bool on){
    if(on){
        m_timer.start(33);
    }
    else{
        m_timer.stop();
    }
}

void ReactorModel::reactorLoop(){
    const double &iterationFlow = m_incomeFlow + m_reactionFlow + m_outgoingFlow;
    // demonstrate flow on reactor display
    m_gasMoles+=iterationFlow;
    double currentPressurePa = molesToBar(m_gasMoles);
    m_pressureBar = currentPressurePa*1e-5; // modelling!
    qDebug() << m_pressureBar << " bar";
    // gates about pressure
    // can't be higher than possible suppply 
    // is pressure limit reached?
    // recalculate income flow based on this limit
    emit pressureChanged(m_pressureBar);
}

double ReactorModel::getPressureBar() const{
    return m_pressureBar; // modelled
}