#include "datacollection.h"
#include <QDebug>

DataCollection::DataCollection(const QString &name) : m_name(name)
{
    m_y.append(0);
}

DataCollection::~DataCollection(){
    qDebug() << "DataCollection destructor + " << m_name;
}
void DataCollection::clearPoints(){
    m_y.clear();
    m_y << 0;
}
void DataCollection::addPoint(const double &val_y){
    m_y.append(val_y);        
}

QVector<double> DataCollection::getValue() const {
    return m_y;
}

QVector<double> DataCollection::getLastToChart() const {
    if(m_y.count() > 120) // last 2 minutes only but stores all
        return m_y.last(120);
    return m_y;
}

double DataCollection::getCurValue() const{
    return m_y.last();
}

ControllerData::ControllerData(const QString &name, const double& A, const double& B) : DataCollection(name),
lin_A(A), lin_B(B)
{

}

ControllerData::~ControllerData(){
    qDebug() << "ControllerData destructor";
}

void ControllerData::setCoeffs(const double& A, const double& B){
    lin_A = A;
    lin_B = B;
}

void ControllerData::addValue(const double &val_y){
    const auto& val = lin_A*val_y + lin_B;
    addPoint(val);
}

void ControllerData::addValue(const double &val_y, const double &minimalValue){
    auto val = lin_A*val_y + lin_B;
    if(val < minimalValue)
        val = 0.0;
    addPoint(val);
}

ExpData::ExpData(const QString &name) : DataCollection(name)
{

}

void ExpData::setData(const QVector<double> &val_y){
    m_y = val_y;
}


