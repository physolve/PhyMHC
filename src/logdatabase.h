#pragma once

#include "datacollection.h"
#include <QElapsedTimer>
#include <QTimer>

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
    DataCollection* tcUp;
    DataCollection* prUp;
    DataCollection* flUp;
    DataCollection* tcDw;
    DataCollection* prDw;
    DataCollection* flDw;

    DataCollection* reactorUps;
    DataCollection* reactorDws;
};