#pragma once

#include "../datacollection.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QSharedPointer>

class TestController : public QObject
{
    Q_OBJECT
    
public:
    TestController(QList<QSharedPointer<ControllerData>> dataStorage, QObject *parent = nullptr);
    virtual ~TestController();
    void startTest();
signals:
    void valueChanged();

private slots:
    void processEvents();

private:
    QElapsedTimer m_programmTime;
    QTimer* m_timer;
    QSharedPointer<ControllerData> time;
    QSharedPointer<ControllerData> upstream;
    QSharedPointer<ControllerData> downstream;
};