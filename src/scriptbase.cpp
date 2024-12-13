#include "scriptbase.h"
#include <math.h>
#include <QFile>

ScriptBase::ScriptBase(QObject *parent) : QObject(parent),
m_mnemoValues{0,0,0,false,0,0,0,false}
{
    sayHello();
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

void ScriptBase::thirdTask(){
    // using data from source to "heat up" reactor
    // timing script normalized function from 293 K to 573 K
}