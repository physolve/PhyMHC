#pragma once
#include "datacollection.h"
#include <QDebug>
#include <QTime>
// struct DataStore{
//     QString name;
//     QString timeStart;
//     QString duration;
//     double currentScalar;
// };

class ScalarCalc : public QObject
{
    Q_OBJECT
    // Q_PROPERTY (QVariantList dataCollection READ getDataCollection NOTIFY dataCollectionChanged)
    // Q_PROPERTY (QString clockTime READ getClockTime NOTIFY clockTimeChanged)
    // Q_PROPERTY (QString scalarStr READ getScalarStr NOTIFY scalarStrChanged)
    // Q_PROPERTY(int runCnt READ getRunCnt NOTIFY runCntChanged)
    Q_PROPERTY (bool exposure READ getExposure WRITE setExposure  NOTIFY exposureChanged)
    Q_PROPERTY (bool append READ getAppend WRITE setAppend NOTIFY appendChanged)
    Q_PROPERTY (bool remove READ getRemove WRITE setRemove NOTIFY removeChanged)
    Q_PROPERTY (double currentScalar READ getCurrentScalar NOTIFY currentScalarChanged)

public:
    explicit ScalarCalc(QObject *parent  = nullptr);
    ~ScalarCalc();
    // Q_INVOKABLE void onFlowToScalarClicked(const QString &name, bool s);
    // Q_INVOKABLE void saveResults(const QUrl &fileName);
    // void startCalc(const QString &name);
    // void stopCalc();
    void setCalcData(DataCollection* time, DataCollection* flowFarAppend, DataCollection* flowNearRemove, DataCollection* reactorCharge);
    void processCalc();
                //  before last, last flow, before last, last time
    void calcScalar(double y0, double y1, qreal x0, qreal x1);
    void setCurrentScalar(double scalar);
    double getCurrentScalar() const;

    void updateFromBackend();

    int getSecondsTime() const;
    QString getClockTime() const;
    // QString getScalarStr() const;
    // int getRunCnt() const;
    // QVariantList getDataCollection() const;
    Q_INVOKABLE void setVolumeValue(double volumeValue);
    void setExposure(bool state);
    bool getExposure() const;
    void setAppend(bool state);
    bool getAppend() const;
    void setRemove(bool state);
    bool getRemove() const;

signals:
    // void dataCollectionChanged();
    // void clockTimeChanged();
    // void scalarStrChanged();
    // void runCntChanged();
    void exposureChanged();
    void appendChanged();
    void removeChanged();
    void currentScalarChanged();
private:
    // QList<DataStore> dataCollection;
    // QString m_currentCollection;
    QString clockTime;
    QTime m_timeStart;
    int m_duration;
    double m_currentScalar;

    bool isExposure;
    bool isAppend;
    bool isRemove;
    // int runCnt;
    // QString scalarStr;
    DataCollection* m_time;
    DataCollection* m_flowFarAppend;
    DataCollection* m_flowNearRemove;
    DataCollection* m_reactorCharge;
    
    double m_previousFlowAppend;
    double m_previousFlowRemove;
    double m_previousTime;
};