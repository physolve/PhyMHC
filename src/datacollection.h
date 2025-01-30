#pragma once
#include <QString>
#include <QMap>
#include <QDebug>
// should be either signal of data changed
// should be Q_OBJECT
enum DataType{
    TYPE_time,
    TYPE_tcUp,
    TYPE_prUp,
    TYPE_flUp,
    TYPE_tcDw,
    TYPE_prDw,
    TYPE_flDw
};

class DataCollection //: public QObject
{
    //Q_OBJECT
public:
    DataCollection(const QString &name);
    virtual ~DataCollection();
    void clearPoints();
    void addPoint(const double &val_y);
    QVector<double> getValue() const;
    QVector<double> getLastToChart() const;
    double getCurValue() const;
    QString m_name;
protected:
    QList<double> m_y; // one second data
};

// time data class

class ControllerData : public DataCollection
{
public:
    ControllerData(const QString &name);
    virtual ~ControllerData();
};

class ExpData : public DataCollection
{
public:
    ExpData(const QString &name, const int &setId);
    void setData(const QVector<double> &val_y);
private:
    unsigned int m_setId;
};

struct Switch{
    QString m_name = "";
    bool m_state = false;
    void setState(bool s){
        m_state = s;
    }
    bool getState() const{
       return m_state; 
    }
    Switch(const QString &name = "unknown", const bool &state = false): m_name(name), m_state(state) { }
    ~Switch(){  }
};