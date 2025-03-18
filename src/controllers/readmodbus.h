#pragma once

#include "readmodbus.h"
#include "settingsmodbus.h"
#include <QModbusDataUnit>
#include <QElapsedTimer>
#include <QTimer>

class ReadModbus : public QObject{
    Q_OBJECT
public:
    ReadModbus(QObject *parent = 0);
    ~ReadModbus();
    void setModbusParameters(const SerialParameters& modbusParameters);
    void connectFlow();
    void disconnectFlow();
    void startReading();
    void stopReading();
    void setModbusRegister(const int& startAddress, const int& readSize);
    void requestFlow(); // read type 
private slots:
    void processEvents();
    void onModbusStateChanged(int state);
    void onReadReady();
private:
    QModbusDataUnit readRequest(int address, int size) const;
    QTimer* m_timer;
    SerialParameters m_modbusParameters;
    int m_currentAdress;
    int m_currentSize;
    QModbusClient *modbusDevice = nullptr;
    int threshold = 0;

};