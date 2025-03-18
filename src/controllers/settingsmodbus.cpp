#include "settingsmodbus.h"

#include <QSerialPortInfo>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SettingsModbus::SettingsModbus(QObject *parent) :
    QObject(parent)
{
    fillPortsInfo();
    m_modbusParameters.port = m_modbusPort;
    m_modbusParameters.description = m_modbusDescription;
    m_modbusParameters.parity = QSerialPort::EvenParity;
    m_modbusParameters.baudRate = QSerialPort::Baud19200;
    m_modbusParameters.dataBits = QSerialPort::Data8;
    m_modbusParameters.stopBits = QSerialPort::OneStop;
    m_modbusParameters.numberOfRetries = 3;
    m_modbusParameters.responseTime = 1000;
    m_modbusParameters.server = 1;
}

SettingsModbus::~SettingsModbus()
{
}

SerialParameters SettingsModbus::serialParameters() const
{
    return m_modbusParameters;
}

void SettingsModbus::fillPortsInfo()
{
    m_descriptions.clear();
    const auto infos = QSerialPortInfo::availablePorts();
    QString port;
    QString description;
    for (const QSerialPortInfo &info : infos) {
        port = info.portName();
        description = info.description();
        m_descriptions[port] = description;
        if(description.startsWith("USB")){
            m_modbusPort = port;
            m_modbusDescription = description;
        }
    }
}