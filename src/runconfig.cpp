#include "runconfig.h"

#include <QDir>
#include <QFile>

RunConfig::RunConfig(QObject *parent) : QObject(parent), m_runLogTimer(new QTimer)
{
    QDir dir("data");
    if (!dir.exists())
        dir.mkpath("data");
    directoryRunNames = dir.entryList(QStringList() << "*.txt",QDir::Files);
    // this should compare string names with configurated name
    todayRuns = todayRunCount();
    qDebug() << "Today runs: " << todayRuns;

    // default frequency 10 sec?
    m_dataWriteFrequency = 10;
    m_runLogTimer->setInterval(m_dataWriteFrequency*1000);
    connect(m_runLogTimer, &QTimer::timeout, this, &RunConfig::writeRunLog);

    // defaults
    m_runParams.runName = "Empty";
    m_runParams.releaseFrom = "Из";
    m_runParams.initialLitresFrom = 0;
    m_runParams.loadTo = "В";
    m_runParams.initialLitresTo = 0;
    m_runParams.upstreamToDownstream = false;
    m_runParams.downstreamToUpstream = false;
    m_runParams.upstreamToAir = false;
    m_runParams.downstreamToAir = false;
    m_runParams.supplyToUpstream = false;
    m_runParams.supplyToDownstream = false;
    m_runParams.baseFileName = QDate::currentDate().toString("yyyy-MM-dd")+"_Из_В_№";
    m_runParams.dayRunCnt = todayRuns;
    m_runParams.logHeaderComment = "Empty";
    m_runParams.totalLitresPass = 0;
    m_runParams.endLitresTo = 0;
    m_runParams.endLitresFrom = 0;
    m_runParams.differenseToFrom = 0;
    m_runParams.clockTime = "00:00:00";
    m_runParams.totalTimeSec = 0;

    emit totalRunsChanged();
}

RunConfig::~RunConfig(){
    qDebug() << "Runconfig destructor";
    tcUp = nullptr;
    prUp = nullptr;
    flUp = nullptr;
    tcDw = nullptr;
    prDw = nullptr;
    flDw = nullptr;
    reactorUps = nullptr;
    reactorDws = nullptr;
}

void RunConfig::setData(DataCollection* ptr, LogType type){
    switch(type){
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

void RunConfig::updateRunParameters(const RunParameters& runParams){
    m_runParams = runParams;
    emit totalLitresChanged();
    emit durationChanged();
}

RunParameters RunConfig::getRunParameters() const{
    return m_runParams;
}

int RunConfig::todayRunCount(){
    // let's find out today run count
    QString compareTo = QDate::currentDate().toString("yyyy-MM-dd");
    auto runs = 0;
    for(const auto& str : directoryRunNames){
        const auto& prepend = str.split('_');
        if(prepend.isEmpty()) continue;
        if(prepend.at(0) == compareTo)
            runs++;
    }
    return runs;
}

void RunConfig::formFileName(){
    auto logNameParams = QString("%1-%2").arg(m_runParams.releaseFrom).arg(m_runParams.loadTo);
    m_runParams.dayRunCnt = todayRuns = todayRunCount();
    emit totalRunsChanged();
    if(todayRuns > 0)
        logNameParams+="_"+QString::number(todayRuns);
    m_runParams.baseFileName = QDate::currentDate().toString("yyyy-MM-dd")+"_"+logNameParams+".txt";
}

// void RunConfig::makeChangesInFileName(){
//     formFileName();
//     emit nameFileGuiChanged();
// }

void RunConfig::logRunCreation(){
    QDir dir("data");
    if (!dir.exists())
        dir.mkpath("data");
    QFile file;
    formFileName();
    m_filePath = dir.filePath(m_runParams.baseFileName);
    file.setFileName(m_filePath);
    if (!file.open(QIODevice::ReadWrite))
        return;
    // startUpHeader
    // upHeader {Reactor 1 info} // {Reactor 2 info}
    // endUpHeader
    QString borderUpHeader;
    for(auto i = 0; i < 50; i++){
        borderUpHeader += "*";
        if(i == 24)
            borderUpHeader+=m_runParams.runName;
    }
    borderUpHeader += "\n";
    QString upHeader;
    configurateHeader(upHeader);
    QString header = "Время\tИстекло\tПоток в LaNi5\tДавление LaNi5\tТемпература LaNi5\tПоток в TiFe\tДавление TiFe\tТемпература TiFe\tЗаряд LaNi5\tЗаряд TiFe";
    QTextStream in(&file);
    QString line;
    line = in.readLine();
    if (line != header) {
        QTextStream head(&file);
        head << borderUpHeader;
        head << upHeader;
        head << "***\tКомментарий:\t" << m_runParams.logHeaderComment << "\n";
        head << "                                                           \n";
        head << "                                                                                           \n";
        // head << "\n";
        head << borderUpHeader;
        head << header << "\n";
    }
    file.close();
}

void RunConfig::configurateHeader(QString &upHeader){
    QString regime;
    QString charge;
    if(m_runParams.upstreamToDownstream){
        regime = "LaNi5 в TiFe";
        charge = QString("%1, %2 л.; %3, %4 л.").arg(m_runParams.releaseFrom).arg(m_runParams.initialLitresFrom)
    .arg(m_runParams.loadTo).arg(m_runParams.initialLitresTo);
    }
    else if(m_runParams.downstreamToUpstream){
        regime = "TiFe в LaNi5";
        charge = QString("%1, %2 л.; %3, %4 л.").arg(m_runParams.releaseFrom).arg(m_runParams.initialLitresFrom)
    .arg(m_runParams.loadTo).arg(m_runParams.initialLitresTo);
    }
    else if(m_runParams.upstreamToAir){
        regime = "LaNi5 в воздух";
        charge = QString("%1, %2 л.").arg(m_runParams.releaseFrom).arg(m_runParams.initialLitresFrom);
    }
    else if(m_runParams.downstreamToAir){
        regime = "TiFe в воздух";
        charge = QString("%1, %2 л.").arg(m_runParams.releaseFrom).arg(m_runParams.initialLitresFrom);
    }
    else if(m_runParams.supplyToUpstream){
        regime = "баллона в LaNi5";
        charge = QString("%1, X л.; %2, %3 л.").arg(m_runParams.releaseFrom).arg(m_runParams.loadTo).arg(m_runParams.initialLitresTo);
    }
    else if(m_runParams.supplyToDownstream){
        regime = "баллона в TiFe";
        charge = QString("%1, X л.; %2, %3 л.").arg(m_runParams.releaseFrom).arg(m_runParams.loadTo).arg(m_runParams.initialLitresTo);
    }
    upHeader+= QString("***\tИз\t\t%1\n").arg(regime);
    upHeader+= QString("***\tЗаряд до:\t%1\n").arg(charge);
}

void RunConfig::startRun(){
    m_runTime.start();
    writeRunLog();
    m_runLogTimer->start();
}

void RunConfig::stopRun(){
    // file close
    m_runLogTimer->stop();
    // ending something
    // ________________
    // you may append additional info into header using readLine to specific line
}

bool RunConfig::isRunLog() const{
    return m_runLogTimer->isActive();
}

void RunConfig::setWriteFrequency(int freq){
    m_dataWriteFrequency = freq;
    m_runLogTimer->setInterval(m_dataWriteFrequency*1000);
}

void RunConfig::toggleWrite(bool state){
    if(state){
        m_runLogTimer->start();
    }
    else{
        m_runLogTimer->stop();
    }
}

void RunConfig::writeRunLog(){
    //put updates to file
    QFile file(m_filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    
    const auto &c_time = m_runTime.elapsed()/1000.0;

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

void RunConfig::insertTotalLitres(){
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadWrite))
        return;
    QTextStream in(&file);
    for(int i = 0; i < 4; ++i){
        in.readLine();
    }
    QTextStream insert(&file);
    insert.seek(in.pos());
    insert << "***\tЛитров прошло:\t" << m_runParams.totalLitresPass << "\n";
    QString charge;
    if(m_runParams.upstreamToDownstream){
        charge = QString("%1, %2 л.; %3, %4 л.").arg(m_runParams.releaseFrom).arg(m_runParams.endLitresFrom)
    .arg(m_runParams.loadTo).arg(m_runParams.endLitresTo);
    }
    else if(m_runParams.downstreamToUpstream){
        charge = QString("%1, %2 л.; %3, %4 л.").arg(m_runParams.releaseFrom).arg(m_runParams.endLitresFrom)
    .arg(m_runParams.loadTo).arg(m_runParams.endLitresTo);
    }
    else if(m_runParams.upstreamToAir){
        charge = QString("%1, %2 л.").arg(m_runParams.releaseFrom).arg(m_runParams.endLitresFrom);
    }
    else if(m_runParams.downstreamToAir){
        charge = QString("%1, %2 л.").arg(m_runParams.releaseFrom).arg(m_runParams.endLitresFrom);
    }
    else if(m_runParams.supplyToUpstream){
        charge = QString("%1, X л.; %2, %3 л.").arg(m_runParams.releaseFrom).arg(m_runParams.loadTo).arg(m_runParams.endLitresTo);
    }
    else if(m_runParams.supplyToDownstream){
        charge = QString("%1, X л.; %2, %3 л.").arg(m_runParams.releaseFrom).arg(m_runParams.loadTo).arg(m_runParams.endLitresTo);
    }
    insert << "***\tЗаряд после:\t" << charge << "\n";
    insert << "***\tЗа время:\t" << m_runParams.clockTime << "\n";

    file.close(); 
}

double RunConfig::getTotalLitres() const{
    return m_runParams.totalLitresPass;
}

QString RunConfig::getDuration() const{
    return m_runParams.clockTime;
}

int RunConfig::getTotalRuns() const{
    return m_runParams.dayRunCnt;
}
