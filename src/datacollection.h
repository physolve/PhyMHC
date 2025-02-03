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

struct guiValues{ // sample
    Q_GADGET
    // it might be linked to json for import and multi-result log
    Q_PROPERTY (double temperatureUpstream MEMBER m_temperatureUpstream)
    Q_PROPERTY (double pressureUpstream MEMBER m_pressureUpstream)
    Q_PROPERTY (double flowUpstream MEMBER m_flowUpstream)
    Q_PROPERTY (double temperatureDownstream MEMBER m_temperatureDownstream)
    Q_PROPERTY (double pressureDownstream MEMBER m_pressureDownstream)
    Q_PROPERTY (double flowDownstream MEMBER m_flowDownstream)
public:
    double m_temperatureUpstream; // C
    double m_pressureUpstream; // bar
    double m_flowUpstream; // slpm
    double m_flowUpstreamMoles; // moles per second
    double m_temperatureDownstream; // C
    double m_pressureDownstream; // bar
    double m_flowDownstream; // slpm
    double m_flowDownstreamMoles; // slpm
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
    ControllerData(const QString &name, const double& A = 1, const double& B = 0);
    virtual ~ControllerData();
    void setCoeffs(const double& A, const double& B);
    void addValue(const double &val_y);
private:
    double lin_A;
    double lin_B;
};

class ExpData : public DataCollection
{
public:
    ExpData(const QString &name);
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