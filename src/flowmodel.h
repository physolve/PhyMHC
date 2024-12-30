#pragma once

#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>

class FlowModel : public QObject
{
    Q_OBJECT

public:
    FlowModel(QObject *parent = 0);
    ~FlowModel();
    void startFlow(double currentFlow, double targetFlow);
    void startCustomFlow(bool on);
    double slpmToMps(double flowSlpm);
    double mpsToSlpm() const;
    void setCurrentPressure(double currentPressure);
    void stopFlow();
    void setFreeVolume(double freeVolume = 10);
signals:
    void flowChanged(double flow);
    void targetReached();

private slots:
    void calculateFlow();

private:
    QTimer m_timer;
    QElapsedTimer m_time;
    double m_startFlow;
    double m_targetFlow;
    double m_currentFlow;

    double m_currentPressure;
    double m_pressureLimit;

    double m_freeVolume;
};
