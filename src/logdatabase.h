#pragma once

#include "datacollection.h"
#include <QObject>
// #include <QFileDialog>
#include <QElapsedTimer>
#include <QTimer>

enum LogType{
    LOG_time,
    LOG_tcUp,
    LOG_prUp,
    LOG_flUp,
    LOG_tcDw,
    LOG_prDw,
    LOG_flDw,
    LOG_reactorUps,
    LOG_reactorDws
};

class LogDataBase : public QObject
{
	Q_OBJECT

public:
	LogDataBase(QObject *parent = 0);
	~LogDataBase();
    void setData(DataCollection* ptr, LogType type);
    void startLog();
    void setWriteFrequency(int freq);
public slots:
    void writeLine(QString line);

private slots:
    void programmLog();

private:
    int m_dataWriteFrequency; //seconds

    QElapsedTimer m_programmTime;
    QTimer* m_logTimer;

    QString m_filePath;
    // pointers for every data
    DataCollection* time;
    DataCollection* tcUp;
    DataCollection* prUp;
    DataCollection* flUp;
    DataCollection* tcDw;
    DataCollection* prDw;
    DataCollection* flDw;

    DataCollection* reactorUps;
    DataCollection* reactorDws;
};