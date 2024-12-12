#include "scriptbase.h"
#include <math.h>
#include <QFile>

ScriptBase::ScriptBase(QObject *parent) : QObject(parent)
{
    sayHello();
}

ScriptBase::~ScriptBase(){
    
}

void ScriptBase::sayHello(){
    m_infoString = "I have been initialized";
}