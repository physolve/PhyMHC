#pragma once

#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>

class HeaterModel : public QObject
{
	Q_OBJECT
    
public:
    HeaterModel(QObject *parent = 0);
	~HeaterModel();
    void startHeating(double currentTemp, double targetTemp);

signals:
    void temperatureChanged(double temp);
    void targetReached();

private slots:
    void calculateTemperature();
private:
	QTimer m_timer;
    QElapsedTimer m_time;

    // change parameters to stucture

    double m_startTemp;
    double m_targetTemp;
    double m_currentTemp;
};