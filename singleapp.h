#ifndef SINGLEAPP_H
#define SINGLEAPP_H

#include <QFile>
#include <QObject>
#include <QApplication>

class SingleApp
{
	Q_OBJECT

public:
	SingleApp(QString filename = "", QString errorMessage = "", QObject* parent = nullptr);

private:
	QFile* f_lock;
};

#endif // SINGLEAPP_H
