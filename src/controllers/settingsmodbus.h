#pragma once

#include <QSerialPort>
#include <QVariant>

struct SerialParameters {
    QString port;
    QString description;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    int responseTime;
    int numberOfRetries;
    int server;
};

class SettingsModbus : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(QVariantMap serialPortList READ serialPortListRead CONSTANT)
public:

    explicit SettingsModbus(QObject *parent = nullptr);
    ~SettingsModbus();
    SerialParameters serialParameters() const;
private:
    void fillPortsInfo();
    void updateSettings();
    QMap<QString, QString> m_descriptions;
    QString m_modbusPort;
    QString m_modbusDescription;
    SerialParameters m_modbusParameters;
};