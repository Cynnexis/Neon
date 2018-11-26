#ifndef NRESOURCES_H
#define NRESOURCES_H

#include <QFile>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

#include "theme.h"
#include "status.h"

class NResources
{
public:
	static QString getNeonDarkJSONPath();
	static QString getNeonLightJSONPath();
	static QString getNeonBaseCSSPath();

	static QString getNeonDarkJSON();
	static QString getNeonLightJSON();
	static QString getNeonBaseCSS();

	static QString getNeonDarkCSS(const Status& status);
	static QString getNeonDarkCSS(const QString& statusName);

	static QString getNeonLightCSS(const Status& status);
	static QString getNeonLightCSS(const QString& statusName);

private:
	static QString read(const QString& filename);
	static QString constructCSS(const QString& statusName, const QString& raw_json, QString css = "");
};

#endif // NRESOURCES_H
