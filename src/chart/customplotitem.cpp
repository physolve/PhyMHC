#include "customplotitem.h"
#include "../lib/qcustomplot.h"
#include <QDebug>
 
CustomPlotItem::CustomPlotItem(QQuickItem* parent) : QQuickPaintedItem(parent),
    // m_time(nullptr), m_sensors(nullptr),
    m_CustomPlot(nullptr), mTag1(nullptr), mTag2(nullptr), backlogSize(10)//, updateTimer(new QTimer)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
 
    connect(this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect(this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );

    // connect(updateTimer, &QTimer::timeout, this, &CustomPlotItem::dataUpdated);
}
 
CustomPlotItem::~CustomPlotItem()
{
    delete mTag1;
    delete mTag2;
    m_time = nullptr;
    m_sensors.clear();
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

CustomPlotItem* CustomPlotItem::getCustomPlot()
{
    return this;
}

void CustomPlotItem::initCustomPlot()
{
    qDebug() << "hz";
    m_CustomPlot = new QCustomPlot;
    m_CustomPlot->setOpenGl(true);
    connect(m_CustomPlot, &QCustomPlot::destroyed, this, [=](){ qDebug() << QString("QCustomPlot (%1) pointer is destroyed ").arg(0); });
    updateCustomPlotSize();
    backgroundCustomPlot();
    setupPlot(m_CustomPlot);
    connect(m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot);
    m_CustomPlot->replot();
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot) {
        m_CustomPlot->setGeometry(0, 0, (int)width(), (int)height());
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotItem::backgroundCustomPlot()
{
    m_CustomPlot->setNoAntialiasingOnDrag(true);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_CustomPlot->xAxis->setTicker(timeTicker);

    // m_CustomPlot->legend->setVisible(true);
    // m_CustomPlot->legend->setBrush(Qt::NoBrush);
    // m_CustomPlot->legend->setTextColor(Qt::white);
    // m_CustomPlot->legend->setBorderPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));

    // set some pens, brushes and backgrounds:
    m_CustomPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis2->setBasePen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis2->setTickPen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->yAxis2->setTickLabelColor(Qt::white);
    m_CustomPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_CustomPlot->yAxis2->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_CustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_CustomPlot->yAxis2->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_CustomPlot->xAxis->grid()->setSubGridVisible(true);
    m_CustomPlot->yAxis2->grid()->setSubGridVisible(true);
    m_CustomPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_CustomPlot->yAxis2->grid()->setZeroLinePen(Qt::NoPen);
    m_CustomPlot->xAxis->setUpperEnding(QCPLineEnding::esBar);
    m_CustomPlot->yAxis2->setUpperEnding(QCPLineEnding::esBar);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_CustomPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_CustomPlot->axisRect()->setBackground(axisRectGradient);
}
void CustomPlotItem::setupPlot(QCustomPlot* customPlot)
{
    customPlot->yAxis->setTickLabels(false);
    connect(customPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    customPlot->yAxis2->setVisible(true);
    customPlot->axisRect()->addAxis(QCPAxis::atRight);
    customPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    customPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags
    
    // create graphs:
    mGraph1 = customPlot->addGraph(customPlot->xAxis, customPlot->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph2 = customPlot->addGraph(customPlot->xAxis, customPlot->axisRect()->axis(QCPAxis::atRight, 1));

    // mGraph2->valueAxis()->setTickLabelColor(Qt::white);

    mGraph2->valueAxis()->setBasePen(QPen(Qt::white, 1));
    mGraph2->valueAxis()->setTickPen(QPen(Qt::white, 1));
    mGraph2->valueAxis()->setSubTickPen(QPen(Qt::white, 1));
    mGraph2->valueAxis()->setTickLabelColor(Qt::white);
    mGraph2->valueAxis()->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    mGraph2->valueAxis()->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    mGraph2->valueAxis()->grid()->setSubGridVisible(true);
    mGraph2->valueAxis()->grid()->setZeroLinePen(Qt::NoPen);
    mGraph2->valueAxis()->setUpperEnding(QCPLineEnding::esBar);

    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    mGraph2->setPen(QPen(QColor(0, 180, 60)));

    mGraph1->setLineStyle(QCPGraph::LineStyle::lsLine);
    mGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(QColor(250, 120, 0)), QBrush(Qt::white), 5));
    mGraph2->setLineStyle(QCPGraph::LineStyle::lsLine);
    mGraph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(QColor(0, 180, 60)), QBrush(Qt::white), 5));
    
    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());
 
    // make left and bottom axes transfer their ranges to right and top axes:
    // connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    // connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    mGraph1->addData(0, 0);
    mGraph2->addData(0, 0); 
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void CustomPlotItem::setDataPointers(DataCollection** ptr, int ptrCnt){
    // not good but it works
    m_time = ptr[0];
    for(auto i = 1; i < ptrCnt; ++i){
        m_sensors.append(ptr[i]);
    }
    // unsafe but fun
}

void CustomPlotItem::dataUpdated()
{
    // if(m_sensors.isEmpty()){
    //     return;
    // }
    const auto &timePoint = m_time->getCurValue(); 

    // mGraph1->setData(m_time->getValue(), m_sensors[0]->getValue()); // use add last data for real time
    // mGraph2->setData(m_time->getValue(), m_sensors[1]->getValue());
    // mGraph1->addData(m_time->getCurValue(), m_sensors[0]->getCurValue());
    int i = 0;
    for(auto ptr : m_sensors){
        m_CustomPlot->graph(i)->addData(timePoint, ptr->getCurValue());
        ++i;
    }
    // for(auto i = 0; i < m_CustomPlot->graphCount(); ++i){
    //     if(m_time->getValue().count()!=m_sensors[i]->getValue().count()){ //sync 
    //         qDebug() << "wrong data in " << m_sensors[i]->m_name;
    //     } // too freq
    //     m_CustomPlot->graph(i)->setData(m_time->getValue(), m_sensors[i]->getValue()); // drawing every point, change to last 300, but only for sensors
    // }
    if(lastPointKey < m_time->getCurValue())
        lastPointKey = m_time->getCurValue();
    m_CustomPlot->xAxis->setRange(m_CustomPlot->xAxis->range().upper, 10, Qt::AlignRight); // 10 and larger by memory scaling?
    m_CustomPlot->xAxis->rescale();
    m_CustomPlot->xAxis->setRange(m_CustomPlot->xAxis->range().upper, backlogSize, Qt::AlignRight);
    // if(rescalingON){
    //     m_CustomPlot->xAxis->setRange(lastPointKey, 10, Qt::AlignRight); // means there a 10 sec
    //     m_CustomPlot->yAxis->rescale();
        // if(m_sensors[0]->getValue().last() != 0)
        //     m_CustomPlot->yAxis->scaleRange(1.1);
    //}
    m_CustomPlot->replot();
}


void CustomPlotItem::paint(QPainter *painter) {
    if (m_CustomPlot) {
        QPixmap picture(boundingRect().size().toSize());
        QCPPainter qcpPainter(&picture);

        m_CustomPlot->toPainter(&qcpPainter);

        painter->drawPixmap(QPoint(), picture);
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    // qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    // qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents(event);
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent(m_CustomPlot, newEvent);
        QCoreApplication::postEvent(m_CustomPlot, newEvent);
    }
}

void CustomPlotItem::wheelEvent(QWheelEvent *event) { 
    routeWheelEvents(event); 
}

void CustomPlotItem::routeWheelEvents(QWheelEvent *event) {
    if (m_CustomPlot) {
        //const auto& beforeScrll = m_CustomPlot->xAxis->range().lower;
        QWheelEvent *newEvent = new QWheelEvent(
            event->position(), event->globalPosition(), event->pixelDelta(),
            event->angleDelta(), event->buttons(), event->modifiers(),
            event->phase(), event->inverted());
        QCoreApplication::postEvent(m_CustomPlot, newEvent);
        // m_CustomPlot->yAxis->rescale(true); //?
        // m_CustomPlot->yAxis->setRangeUpper(m_CustomPlot->yAxis->range().upper*1.1);
        // const auto& afterScrl = m_CustomPlot->xAxis->range().lower;
        // if((beforeScrll - afterScrl) > 0){
        //     backlogSize += 10;
        // }
        // else if(backlogSize > 10) backlogSize -= 10;
    }
}

void CustomPlotItem::onCustomReplot()
{
    update();

    // m_CustomPlot->xAxis->rescale();
    mGraph1->rescaleValueAxis(false, true);
    mGraph2->rescaleValueAxis(false, true);
    // m_CustomPlot->xAxis->setRange(m_CustomPlot->xAxis->range().upper, 10, Qt::AlignRight);

    const auto &last_val = m_CustomPlot->graph(0)->keyAxis()->range().upper; // i need index!
    // bool range = true;
    // const auto &rng_i = m_CustomPlot->graph(0)->getKeyRange(range);
    int graph1Index = mGraph1->findEnd(last_val, false);
    int graph2Index = mGraph2->findEnd(last_val, false);
    double graph1Value = 0;
    double graph2Value = 0;
    if(graph1Index > 0){
        graph1Value = mGraph1->dataMainValue(graph1Index-1);
        graph2Value = mGraph2->dataMainValue(graph2Index-1);
    }
    mTag1->updatePosition(graph1Value);
    mTag2->updatePosition(graph2Value);
    mTag1->setText(QString::number(graph1Value, 'g', 2));
    mTag2->setText(QString::number(graph2Value, 'g', 2));
}