#include "controllerbase.h"
#include <windows.h>
// #include "../lib/USBIO_CSWrapper.h"
// #pragma comment(lib, "ICPDAS_USBIO.lib")
BYTE m_byAITotal;
BYTE m_byDOTotal;

ControllerBase::ControllerBase(QObject *parent) : 
    QObject(parent), m_timer(new QTimer)
{
    // connect(m_timer, &QTimer::timeout, this, &ControllerBase::processEvents);
}

ControllerBase::~ControllerBase(){
    // if(m_timer->isActive()) m_timer->stop();
}

IcpAICtrl::IcpAICtrl(QList<QSharedPointer<ControllerData>> dataStorage, QObject *parent) : 
    ControllerBase(parent)
{
    
}

IcpAICtrl::~IcpAICtrl(){

}