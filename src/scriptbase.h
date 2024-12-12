#pragma once

#include <QDebug>
#include <QVariant>
static const double Rgas = 8.31446;

class ScriptBase : public QObject
{
	Q_OBJECT
	Q_PROPERTY (QString infoString MEMBER m_infoString NOTIFY infoStringChanged)
public:
    ScriptBase(QObject *parent = 0);
	~ScriptBase();

signals:
	void infoStringChanged();

private:
	void sayHello();

	QString m_infoString;
};