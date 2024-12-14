#include "scriptbase.h"

ScriptBase::ScriptBase(QObject *parent) : QObject(parent),
m_mnemoValues{0,0,0,false,0,0,0,false}, m_targetValues{0}, m_heaterModel()
{
    sayHello();
    connect(&m_heaterModel, &HeaterModel::temperatureChanged, this, &ScriptBase::updateHeating);
    connect(&m_heaterModel, &HeaterModel::targetReached, [=]( ) { 
        emit thirdTaskDone(); 
    });
}

ScriptBase::~ScriptBase(){
}

void ScriptBase::sayHello(){
    m_infoString = "I have been initialized";
}

void ScriptBase::firstTask(){
    m_infoString += "\n";
    m_infoString += "Now perform an action";
    emit infoStringChanged();
}

void ScriptBase::secondTask(){
    m_mnemoValues.m_temperatureUpstream = 27.3;
    m_mnemoValues.m_pressureUpstream = 1.01;
    m_mnemoValues.m_flowUpstream = 0.0001;
    m_mnemoValues.m_valveUpstream = true;
    m_mnemoValues.m_temperatureDownstream = 27.3;
    m_mnemoValues.m_pressureDownstream = 1.01;
    m_mnemoValues.m_flowDownstream = 0.0001;
    m_mnemoValues.m_valveDownstream = true;
    emit mnemoChanged();
}

mnemoValues ScriptBase::getMnemo() const{
    return m_mnemoValues;
}

void ScriptBase::thirdTask(){ // make off signal (false)
    // using data from source to "heat up" reactor
    // timing script normalized function from 293 K to 573 K
    m_targetValues.m_tempTargetUpstream = 300;
    m_targetValues.m_tempStartUpstream = m_mnemoValues.m_temperatureUpstream;
    // start timer to model time
    m_heaterModel.startHeating(m_mnemoValues.m_temperatureUpstream, m_targetValues.m_tempTargetUpstream);
}

targetValues ScriptBase::getTargetValues() const{
    return m_targetValues;
}

void ScriptBase::updateHeating(double temp){
    m_mnemoValues.m_temperatureUpstream = temp;
    emit mnemoChanged();

    // connect to heater color

}