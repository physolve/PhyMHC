#pragma once

#include "datacollection.h"
#include <QTimer>
#include <QDebug>
#include <QElapsedTimer>

struct RunParameters{
    QString runName;
    QString releaseFrom;
    double initialLitresFrom;
    QString loadTo;
    double initialLitresTo;
    bool upstreamToDownstream;
    bool downstreamToUpstream;
    bool upstreamToAir;
    bool downstreamToAir;
    QString baseFileName;
    int dayRunCnt;
    QString logHeaderComment;
    double totalLitresPass;
    double endLitresTo;
    double endLitresFrom;
    double differenseToFrom;
    QString clockTime;
    int totalTimeSec;
};

class RunConfig : public QObject
{
	Q_OBJECT
    Q_PROPERTY (double totalLitres READ getTotalLitres NOTIFY totalLitresChanged)
    Q_PROPERTY (QString duration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY (int totalRuns READ getTotalRuns NOTIFY totalRunsChanged)
    // Q_PROPERTY (QString nameFileGui READ getNameFileGui NOTIFY nameFileGuiChanged)
public:
    RunConfig(QObject *parent = 0);
	~RunConfig();
    void setData(DataCollection* ptr, LogType type);
    void updateRunParameters(const RunParameters& runParams);
    RunParameters getRunParameters() const;
    int todayRunCount();
    void formFileName();
    void logRunCreation();
    void startRun();
    void stopRun();
    bool isRunLog() const;
    void toggleWrite(bool state);
    void setWriteFrequency(int freq);
    // Q_INVOKABLE void makeChangesInFileName();
    double getTotalLitres() const;
    QString getDuration() const;
    int getTotalRuns() const;
    // QString getNameFileGui() const;
    void insertTotalLitres();
signals:
    void totalLitresChanged();
    void durationChanged();
    void totalRunsChanged();
    // void nameFileGuiChanged();

private slots:
    void writeRunLog();

private:
    QElapsedTimer m_runTime;
    int m_dataWriteFrequency; //seconds
    QTimer* m_runLogTimer;

    // change parameters to stucture
    RunParameters m_runParams;

    QStringList directoryRunNames;
    int todayRuns;
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