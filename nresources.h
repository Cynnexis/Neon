#ifndef NRESOURCES_H
#define NRESOURCES_H

#include <iostream>

#include <QFile>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QRegularExpression>
#include <QDebug>

#include "theme.h"
#include "status.h"
#include "ioexception.h"

using namespace std;

namespace NResources
{
	QString getNeonDarkJSONPath();
	QString getNeonLightJSONPath();
	QString getNeonBaseCSSPath();

	QString getNeonDarkJSON();
	QString getNeonLightJSON();
	QString getNeonBaseCSS();

	QString getNeonDarkCSS(const Status& status);
	QString getNeonDarkCSS(const QString& statusName);

	QString getNeonLightCSS(const Status& status);
	QString getNeonLightCSS(const QString& statusName);

	QString merge(QString css, QMap<QString, QString> vars);
};

#endif // NRESOURCES_H
