#include "scriptbase.h"

static const double Rgas = 8.31446;
static const double abscTemp = 273.15;

ScriptBase::ScriptBase(QObject *parent) : QObject(parent),
m_mnemoValues{0,0,0,false,0,0,0,false}, m_targetValues{0}, m_heaterModel(), m_flowModel(), m_reactorModel()
{
    sayHello();
    connect(&m_heaterModel, &HeaterModel::temperatureChanged, this, &ScriptBase::updateHeating);
    connect(&m_heaterModel, &HeaterModel::targetReached, [=]( ) { 
        emit thirdTaskDone(); 
    });
    connect(&m_flowModel, &FlowModel::flowChanged, this, &ScriptBase::updateFlow);
    connect(&m_flowModel, &FlowModel::targetReached, [=]( ) { 
        emit fourthTaskDone(); 
    });
    connect(&m_reactorModel, &ReactorModel::pressureChanged, this, &ScriptBase::reactorToFlowChange);
    connect(&m_reactorModel, &ReactorModel::pressureChanged, this, &ScriptBase::updatePressure);
}

ScriptBase::~ScriptBase(){
    qDebug() << "Script base destructor";
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
    m_mnemoValues.m_flowUpstreamMoles = 0.000001;
    m_mnemoValues.m_valveUpstream = false;
    m_mnemoValues.m_temperatureDownstream = 27.3;
    m_mnemoValues.m_pressureDownstream = 1.01;
    m_mnemoValues.m_flowDownstream = 0.0001;
    m_mnemoValues.m_flowDownstreamMoles = 0.000001;
    m_mnemoValues.m_valveDownstream = false;

    m_mnemoValues.m_valveDownstream = false;

    m_targetValues.m_tempTargetUpstream = 300;

    m_targetValues.m_flowTargetUpstream = 1;

    const double &tempAbs = m_mnemoValues.m_temperatureUpstream + abscTemp;
    molesMnemo = (m_mnemoValues.m_pressureUpstream*10*1e-6)/(Rgas*tempAbs);

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

void ScriptBase::updateHeating(const double &temp){
    m_mnemoValues.m_temperatureUpstream = temp;
    emit mnemoChanged();
}

void ScriptBase::fourthTask(){
    m_targetValues.m_flowTargetUpstream = 50; // slpm
    m_targetValues.m_flowStartUpstream = m_mnemoValues.m_flowUpstreamMoles;
    m_flowModel.setCurrentPressure(m_mnemoValues.m_pressureUpstream);
    m_flowModel.startFlow(m_mnemoValues.m_flowUpstreamMoles, m_targetValues.m_flowTargetUpstream); // moles
}

void ScriptBase::updateFlow(const double &flow){
    if(m_mnemoValues.m_valveUpstream){
        m_flowModel.setFreeVolume(m_reactorModel.getVolumeReactor());
        
        m_reactorModel.incomeMoleFlow(flow); //moles
        m_mnemoValues.m_flowUpstreamMoles = flow; // from Mps to slpm
        m_mnemoValues.m_flowUpstream = m_flowModel.mpsToSlpm();

    }
    else{
        m_flowModel.setFreeVolume();
        const double &tempAbs = m_mnemoValues.m_temperatureUpstream + abscTemp;
        const double &volumeMCube = 10*1e-6;
        double currentPressurePa = (flow*Rgas*tempAbs)/volumeMCube;
        
        double pressureBar = currentPressurePa*1e-5; // modelling!
        m_flowModel.setCurrentPressure(pressureBar);
    }
    emit mnemoChanged();
    
}

void ScriptBase::updatePressure(const double &pressure){
    m_mnemoValues.m_pressureUpstream = pressure;
    emit mnemoChanged();
}

void ScriptBase::fifthTask(bool on){
    if(on){
        m_reactorModel.setCurrentTemp(m_mnemoValues.m_temperatureUpstream);
        m_reactorModel.initializeState();


        m_mnemoValues.m_valveUpstream = true;
        emit mnemoChanged();

        fourthTask();
        valveUpstreamOpened();
    }
    else{
        m_reactorModel.startReactionLoop(false);
    }
}

void ScriptBase::valveUpstreamOpened(){
    m_reactorModel.incomeMoleFlow(m_mnemoValues.m_flowUpstreamMoles);
    m_reactorModel.startReactionLoop(true);
}

void ScriptBase::valveUpstreamClosed(){
    m_reactorModel.startReactionLoop(false);
}

void ScriptBase::reactorToFlowChange(const double &pressure){
    m_flowModel.setCurrentPressure(pressure);
}

void ScriptBase::startCustomFlow(bool on){
    m_flowModel.startCustomFlow(on);
}

void ScriptBase::manualPrepare(){
    secondTask();
    m_flowModel.setCurrentPressure(m_mnemoValues.m_pressureUpstream);
}

void ScriptBase::valveUpstreamChanged(bool on){
    m_mnemoValues.m_valveUpstream = on;
    emit mnemoChanged();
    if(on){
        valveUpstreamOpened();
    }
    else{
        valveUpstreamClosed();
    }
}

void ScriptBase::valveVacuumChanged(bool on){
    m_mnemoValues.m_valveVacuum = on;
    emit mnemoChanged();
    if(on){
        if(m_mnemoValues.m_valveUpstream){
            m_mnemoValues.m_pressureUpstream = 1.01;
            emit mnemoChanged();
        }
        m_flowModel.setCurrentPressure(1.01);
        const double &tempAbs = m_mnemoValues.m_temperatureUpstream + abscTemp;
        molesMnemo = (m_mnemoValues.m_pressureUpstream*10*1e-6)/(Rgas*tempAbs);
        m_reactorModel.outgoingFlow(-1);
    }
    else{
        
    }
}

void ScriptBase::sampleSwitchChanged(bool on){
    m_reactorModel.reactionFlow(on);
}