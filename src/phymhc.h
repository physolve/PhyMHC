#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>

#include "scriptbase.h"

class PhyMHC : public QApplication
{
    Q_OBJECT

public:
    PhyMHC(int &argc, char **argvm);
    ~PhyMHC();
private:
    void initGUI();
    ScriptBase m_scriptDefault;
    QQmlApplicationEngine m_engine;

};