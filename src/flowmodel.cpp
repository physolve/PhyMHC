#include "flowmodel.h"

static const double Rgas = 8.31446;
static const double abscTemp = 273.15;

FlowModel::FlowModel(QObject *parent) : QObject(parent), m_timer()
{
    connect(&m_timer, &QTimer::timeout, this, &FlowModel::calculateFlow);
    m_pressureLimit = 10; // bar
    m_startFlow = 0.000001;
    m_freeVolume = 10;
}

FlowModel::~FlowModel(){
   if(m_timer.isActive()) m_timer.stop();
}

void FlowModel::setFreeVolume(double freeVolume){
    m_freeVolume = freeVolume;
}

void FlowModel::startFlow(double currentFlow, double targetFlow){
    m_currentFlow = m_startFlow = currentFlow; // mps
    m_targetFlow = slpmToMps(targetFlow); // mps
    m_time.start();
    m_timer.start(33);
}


void FlowModel::startCustomFlow(bool on){
    if(on){
        m_timer.start(33);
    }
    else{
        m_timer.stop();
    }
}

void FlowModel::stopFlow(){
    m_timer.stop();
}

double FlowModel::slpmToMps(double flowSlpm){ //moles
    return (flowSlpm * 100)/(60 * Rgas * abscTemp); //0.001 * 10e5
}

// define reverse
double FlowModel::mpsToSlpm() const{ 
    return (60 * Rgas * abscTemp * m_currentFlow)/100;
}


void FlowModel::setCurrentPressure(double currentPressure){
    m_currentPressure = currentPressure;
}

void FlowModel::calculateFlow(){
    // write Cumulative Normal Distribution Function for gas flow
    double tau = 30.0; // Time constant (adjust as needed)
    double dt = m_time.elapsed()/1000;
    
    // supply
    //double flowChange = (m_targetFlow - m_currentFlow) * 0.01; // (1 - exp(-dt / tau));
    m_currentFlow = (1 - m_currentPressure/m_pressureLimit)*m_freeVolume*0.00001;
    if(m_currentFlow < 1e-6) m_currentFlow = 0;
    emit flowChanged(m_currentFlow);
    // qDebug() << m_currentFlow << "\t" << m_targetFlow << "\t" << abs(m_currentFlow - m_targetFlow);
    // if (m_currentFlow > m_targetFlow) { // Tolerance check, instead use check from pressure
    //     m_timer.stop();
    //     emit targetReached();
    // }
    // f(t) = 100/(1+)
    // defined by valve state and pressure without reactor
}