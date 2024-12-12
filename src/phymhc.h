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
    QQmlApplicationEngine m_engine;
    ScriptBase m_scriptDefault;

};