#pragma once

#include <QObject>
#include <QDebug>

#include "heatermodel.h"
#include "flowmodel.h"
#include "reactormodel.h"

struct mnemoValues{ // sample
    Q_GADGET
    // it might be linked to json for import and multi-result log
    Q_PROPERTY (double temperatureUpstream MEMBER m_temperatureUpstream)
    Q_PROPERTY (double pressureUpstream MEMBER m_pressureUpstream)
    Q_PROPERTY (double flowUpstream MEMBER m_flowUpstream)
    Q_PROPERTY (bool valveUpstream MEMBER m_valveUpstream)
    Q_PROPERTY (double temperatureDownstream MEMBER m_temperatureDownstream)
    Q_PROPERTY (double pressureDownstream MEMBER m_pressureDownstream)
    Q_PROPERTY (double flowDownstream MEMBER m_flowDownstream)
    Q_PROPERTY (bool valveDownstream MEMBER m_valveDownstream)
    Q_PROPERTY (bool valveVacuum MEMBER m_valveVacuum)
public:
    double m_temperatureUpstream; // C
    double m_pressureUpstream; // bar
    double m_flowUpstream; // slpm
    double m_flowUpstreamMoles; // moles per second
	bool m_valveUpstream; // state
    double m_temperatureDownstream; // C
    double m_pressureDownstream; // bar
    double m_flowDownstream; // slpm
    double m_flowDownstreamMoles; // slpm
	bool m_valveDownstream; // state

	bool m_valveVacuum; // state
};

struct targetValues{
    Q_GADGET
    // it might be linked to json for import and multi-result log
    Q_PROPERTY (double tempTargetUpstream MEMBER m_tempTargetUpstream)
    Q_PROPERTY (double tempStartUpstream MEMBER m_tempStartUpstream)
    Q_PROPERTY (double presTargetUpstream MEMBER m_presTargetUpstream)
    Q_PROPERTY (double presStartUpstream MEMBER m_presStartUpstream)
    Q_PROPERTY (double flowTargetUpstream MEMBER m_flowTargetUpstream)
    Q_PROPERTY (double flowStartUpstream MEMBER m_flowStartUpstream)
public:
    double m_tempTargetUpstream; // C
    double m_tempStartUpstream; // C
    double m_presTargetUpstream; // bar
    double m_presStartUpstream; // bar
    // calculate press depending on flow
    // but use target to stop Flow
    // and use start to calculate change
    double m_flowTargetUpstream; // slpm
    double m_flowStartUpstream; // slpm
};

class ScriptBase : public QObject
{
	Q_OBJECT
	Q_PROPERTY (QString infoString MEMBER m_infoString NOTIFY infoStringChanged)
    Q_PROPERTY (mnemoValues mnemo READ getMnemo NOTIFY mnemoChanged) //WRITE setExpTimingStruct 
    Q_PROPERTY (targetValues targetvals READ getTargetValues) // NOTIFY mnemoChanged

public:
    ScriptBase(QObject *parent = 0);
	~ScriptBase();
	Q_INVOKABLE void firstTask();
	Q_INVOKABLE void secondTask();
	Q_INVOKABLE void thirdTask();
    Q_INVOKABLE void fourthTask();
    Q_INVOKABLE void fifthTask(bool on);
    Q_INVOKABLE void startCustomFlow(bool on);
    Q_INVOKABLE void manualPrepare();
    Q_INVOKABLE void valveUpstreamChanged(bool on);
    Q_INVOKABLE void valveVacuumChanged(bool on);
    Q_INVOKABLE void sampleSwitchChanged(bool on);

signals:
	void infoStringChanged();
	void mnemoChanged();
    void thirdTaskDone();
    void fourthTaskDone();

private slots:
    void updateHeating(const double &temp);
    void updateFlow(const double &flow);
    void updatePressure(const double &pressure);
    void valveUpstreamOpened();
    void valveUpstreamClosed();
    void reactorToFlowChange(const double &pressure);

private:
	void sayHello();
    double currentPressureMnemo();
	QString m_infoString;
	mnemoValues m_mnemoValues;
    mnemoValues getMnemo() const;
    targetValues m_targetValues;
    targetValues getTargetValues() const;
    HeaterModel m_heaterModel;
    FlowModel m_flowModel;
    ReactorModel m_reactorModel;
    double molesMnemo;
};