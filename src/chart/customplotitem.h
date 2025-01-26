#pragma once

#include <QtQuick>
#include "../lib/qcustomplot.h"
#include "../datacollection.h"
#include "axistag.h"


class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();

    Q_INVOKABLE CustomPlotItem* getCustomPlot();

    void paint( QPainter* painter );

    void initCustomPlot();
    void backgroundCustomPlot();
    void setupPlot(QCustomPlot* customPlot);

    void setDataPointers(DataCollection* ptr, DataType type);
protected:
    void routeMouseEvents( QMouseEvent* event );
    void routeWheelEvents(QWheelEvent *event);
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent *event);

private:
    QCustomPlot* m_CustomPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
    DataCollection* m_time;
    // DataCollection** m_sensors; // from controllers
    QVector<DataCollection*> m_sensors;
    // QTimer* updateTimer;
    bool rescalingON;
    int backlogSize;
public slots:
    void dataUpdated();

private slots:
    void graphClicked(QCPAbstractPlottable* plottable);
    void onCustomReplot();
    void updateCustomPlotSize();
};