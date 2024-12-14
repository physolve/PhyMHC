#pragma once

#include <QObject>
#include <QDebug>

#include "heatermodel.h"

static const double Rgas = 8.31446;

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
public:
    double m_temperatureUpstream; // C
    double m_pressureUpstream; // bar
    double m_flowUpstream; // bar/min
	bool m_valveUpstream; // state
    double m_temperatureDownstream; // C
    double m_pressureDownstream; // bar
    double m_flowDownstream; // bar/min
	bool m_valveDownstream; // state
};

struct targetValues{
    Q_GADGET
    // it might be linked to json for import and multi-result log
    Q_PROPERTY (double tempTargetUpstream MEMBER m_tempTargetUpstream)
    Q_PROPERTY (double tempStartUpstream MEMBER m_tempStartUpstream)
public:
    double m_tempTargetUpstream; // C
    double m_tempStartUpstream; // C
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

signals:
	void infoStringChanged();
	void mnemoChanged();
    void reactorChanged(double intence);
    void thirdTaskDone();

private slots:
    void updateHeating(double temp);

private:
	void sayHello();
	
	QString m_infoString;
	mnemoValues m_mnemoValues;
    mnemoValues getMnemo() const;
    targetValues m_targetValues;
    targetValues getTargetValues() const;
    HeaterModel m_heaterModel;
};