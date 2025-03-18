#include "readmodbus.h"
#include <QModbusRtuSerialClient>

ReadModbus::ReadModbus(QObject* parent) : 
    QObject(parent), m_timer(new QTimer), modbusDevice(new QModbusRtuSerialClient(this))
{
    // connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
    //     setLogText(modbusDevice->errorString()); // log under
    // });

    if (!modbusDevice) {
        // setLogText("Could not create Modbus client."); // log under
    } else {
        connect(modbusDevice, &QModbusClient::stateChanged,
                this, &ReadModbus::onModbusStateChanged);
    }
    connect(m_timer, &QTimer::timeout, this, &ReadModbus::processEvents);
}

ReadModbus::~ReadModbus(){
    if(m_timer->isActive()) m_timer->stop();
    delete modbusDevice;
    delete m_timer;
}

void ReadModbus::setModbusParameters(const SerialParameters& modbusParameters){
    m_modbusParameters = modbusParameters;
}

void ReadModbus::connectFlow(){
    if (!modbusDevice)
        return;
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_modbusParameters.port);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, m_modbusParameters.parity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_modbusParameters.baudRate);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m_modbusParameters.dataBits);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m_modbusParameters.stopBits);
    modbusDevice->setTimeout(m_modbusParameters.responseTime);
    modbusDevice->setNumberOfRetries(m_modbusParameters.numberOfRetries);
    if (!modbusDevice->connectDevice()) {
        // setLogText(tr("Connect failed: ") + modbusDevice->errorString()); // log
    }
    else{
        // setLogText("Connected to " + m_settings.m_portEdit + "\nTemperature address: 41272 (x2)\nFlow address: 41216 (x2)");
    }
}

void ReadModbus::disconnectFlow(){
    if (!modbusDevice)
        return;
    modbusDevice->disconnectDevice();
}

void ReadModbus::startReading(){
    threshold = 0;
    m_timer->start(1000);
}

void ReadModbus::processEvents(){
    // current adress, size
    requestFlow();
}

void ReadModbus::setModbusRegister(const int& startAddress, const int& readSize){
    m_currentAdress = startAddress;
    m_currentSize = readSize;
}

void ReadModbus::requestFlow(){
    if (!modbusDevice)
        return;
    // address and size check
    if (auto *reply = modbusDevice->sendReadRequest(
        readRequest(m_currentAdress, m_currentSize),
            m_modbusParameters.server)) {
        if(!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &ReadModbus::onReadReady);
        }
        else{
            delete reply;
        }
    }
    else{
        // setLogText(tr("Read error: ") + modbusDevice->errorString())
        m_timer->stop();
    }
}

QModbusDataUnit ReadModbus::readRequest(int address, int size) const
{
    const auto table = QModbusDataUnit::HoldingRegisters;
    quint16 numberOfEntries = quint16(size);
    return QModbusDataUnit(table, address, numberOfEntries);
}

void ReadModbus::onModbusStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
}

void ReadModbus::onReadReady(){
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        // auto type = checkType(unit.startAddress());
        // if(type.isEmpty()){
        //     replyTreat(unit.startAddress(), unit.values());
        // }
        // else{
        //     replyTreat(type, unit.values());
        // }
    }
}
