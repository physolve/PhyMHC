#include "heatermodel.h"

HeaterModel::HeaterModel(QObject *parent) : QObject(parent), m_timer()
{
    connect(&m_timer, &QTimer::timeout, this, &HeaterModel::calculateTemperature);
}

HeaterModel::~HeaterModel(){
    if(m_timer.isActive()) m_timer.stop();
}

void HeaterModel::startHeating(double currentTemp, double targetTemp){
    m_currentTemp = m_startTemp = currentTemp;
    m_targetTemp = targetTemp;
    m_time.start();
    m_timer.start(33);
}

void HeaterModel::calculateTemperature(){ // heating
    // Implement your temperature calculation logic here.  This is a placeholder.
    // You'll likely need to incorporate startTemp, targetTemp, and possibly m_time.
    // Consider using a transfer function to model the heating process.  A simple example:
    double tau = 30.0; // Time constant (adjust as needed)
    double dt = m_time.elapsed()/1000;
    double tempChange = (m_targetTemp - m_startTemp) * 0.01;// (1 - exp(-dt / tau));
    m_currentTemp += tempChange;
    // Emit a signal to update the UI with the new temperature.  You'll need to define this signal in heatermodel.h
    emit temperatureChanged(m_currentTemp);

    // Stop the timer if the target temperature is reached (or add other stop conditions).
    if (m_currentTemp >= m_targetTemp) { // Adjust tolerance as needed
        m_timer.stop();
        emit targetReached();
    }

}