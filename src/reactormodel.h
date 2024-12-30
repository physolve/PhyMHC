#pragma once

#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>

class ReactorModel : public QObject
{
	Q_OBJECT
    
public:
    ReactorModel(QObject *parent = 0);
    ~ReactorModel();

    void initializeState();
    void incomeMoleFlow(double moles);
    
    void reactionFlow(bool on);

    void outgoingFlow(double moles);

    void setCurrentTemp(const double &temp);

    double getPressureBar() const;

    void startReactionLoop(bool on);

    double getVolumeReactor() const;
signals:
    void pressureChanged(const double &pressure);

private slots:
    void reactorLoop();

private:
    QTimer m_timer;
    QElapsedTimer m_time;

    double molesToBar(const double &moles) const;
    double barToMoles(const double &bar) const;
    

    double m_incomeFlow;
    double m_reactionFlow;
    double m_outgoingFlow;
    double m_gasMoles;
    double m_temperature; // C
    double m_pressureBar; // bar

    double m_pressureBarStart;
    double m_temperatureStart;
    double m_gasMolesStart;
    bool m_valveStateStart;
    //parameters
    const double volumeReactor; // cm3
    const double volumePath; // cm3
};