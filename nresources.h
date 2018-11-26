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
};

#endif // NRESOURCES_H
