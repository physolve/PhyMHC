#include "logdatabase.h"
#include <QDir>
#include <QFile>
LogDataBase::LogDataBase(QObject* parent) : QObject(parent), m_logTimer(new QTimer)
{
    QDir dir("data");
    if (!dir.exists())
        dir.mkpath("data");
    QFile file;
    m_filePath = dir.filePath(QString("log-%1.txt").arg(QDate::currentDate().toString()));
    file.setFileName(m_filePath);
    if (!file.open(QIODevice::ReadWrite))
        return;
    QString line;
    // {Reactor 1 info} // {Reactor 2 info}
    QString header = "Time\tElapsed\tFlowUps\tPressureUps\tTemperatureUps\tFlowDws\tPressureDws\tTemperatureDws\tReactorChargeUps\tReactorChargeDws";
    QTextStream in(&file);
    line = in.readLine();
    if (line != header) {
        QTextStream head(&file);
        head << header << "\n";
    }
    file.close();
    // default frequency 10 sec?
    m_dataWriteFrequency = 10;
    m_logTimer->setInterval(m_dataWriteFrequency*1000);
    connect(m_logTimer, &QTimer::timeout, this, &LogDataBase::programmLog);

    m_programmTime.start();
}

LogDataBase::~LogDataBase(){
    if(m_logTimer->isActive()) m_logTimer->stop();
    // file close if so
    // clear pointers
    time = nullptr;
    tcUp = nullptr;
    prUp = nullptr;
    flUp = nullptr;
    tcDw = nullptr;
    prDw = nullptr;
    flDw = nullptr;
    reactorUps = nullptr;
    reactorDws = nullptr;
}

void LogDataBase::setData(DataCollection* ptr, LogType type){
    switch(type){
        case LogType::LOG_time: time = ptr; break;
        case LogType::LOG_tcUp: tcUp = ptr; break;
        case LogType::LOG_prUp: prUp = ptr; break;
        case LogType::LOG_flUp: flUp = ptr; break;
        case LogType::LOG_tcDw: tcDw = ptr; break;
        case LogType::LOG_prDw: prDw = ptr; break;
        case LogType::LOG_flDw: flDw = ptr; break;
        case LogType::LOG_reactorUps: reactorUps = ptr; break;
        case LogType::LOG_reactorDws: reactorDws = ptr; break;
        default: qDebug() << "unknown type";
    }
}

void LogDataBase::setWriteFrequency(int freq){
    m_dataWriteFrequency = freq;
    m_logTimer->setInterval(m_dataWriteFrequency*1000);
}

void LogDataBase::startLog(){
    m_logTimer->start();
}

void LogDataBase::writeLine(QString line){
    QFile file(m_filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << QTime::currentTime().toString() << "\t";
    out << line << "\n";
}

void LogDataBase::programmLog(){
    QFile file(m_filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    
    const auto &c_time = m_programmTime.elapsed()/1000.0;

    // line: "Time\tElapsed\tFlowUps\tPressureUps\tTemperatureUps\tFlowDws\tPressureDws\tTemperatureDws\tAccumReactorUps\tAccumReactorDws"
    QString line;
    line+= QTime::currentTime().toString() + "\t";
    line+= QString::number(c_time) + "\t";
    line+= QString::number(flUp->getCurValue()) + "\t";
    line+= QString::number(prUp->getCurValue()) + "\t";
    line+= QString::number(tcUp->getCurValue()) + "\t";
    line+= QString::number(flDw->getCurValue()) + "\t";
    line+= QString::number(prDw->getCurValue()) + "\t";
    line+= QString::number(tcDw->getCurValue()) + "\t";
    line+= QString::number(reactorUps->getCurValue()) + "\t";
    line+= QString::number(reactorDws->getCurValue()) + "\t";

    out << line << "\n";
}