#include "nresources.h"

QString read(const QString& filename);
QString constructCSS(const QString& statusName, const QString& raw_json, QString css = "");

QString NResources::getNeonDarkJSONPath() {
#ifdef QT_DEBUG
	return "res/css/neon_light.css";
#else
	return ":/css/neon_light";
#endif
}

QString NResources::getNeonLightJSONPath() {
#ifdef QT_DEBUG
	return "res/css/neon_dark.css";
#else
	return ":/css/neon_dark";
#endif
}

QString NResources::getNeonBaseCSSPath() {
#ifdef QT_DEBUG
	return "res/css/neon_base.css";
#else
	return ":/css/neon_base";
#endif
}

QString NResources::getNeonDarkJSON() {
	return read(getNeonDarkJSONPath());
}

QString NResources::getNeonLightJSON() {
	return read(getNeonLightJSONPath());
}

QString NResources::getNeonBaseCSS() {
	return read(getNeonBaseCSSPath());
}

QString NResources::getNeonDarkCSS(const Status& status) {
	return getNeonDarkCSS(status.getName());
}
QString NResources::getNeonDarkCSS(const QString& statusName) {
	return constructCSS(statusName, getNeonDarkJSON());
}

QString NResources::getNeonLightCSS(const Status& status) {
	return getNeonLightCSS(status.getName());
}
QString NResources::getNeonLightCSS(const QString& statusName) {
	return constructCSS(statusName, getNeonLightJSON());
}

/* PRIVATE FUNCTIONS */

QString read(const QString& filename) {
	QFile f(filename);

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		throw "File not found";

	QString result = f.readAll();
	f.close();

	return result;
}
QString constructCSS(const QString& statusName, const QString& raw_json, QString css) {
	if (css == "")
		css = NResources::getNeonBaseCSS();

	QJsonDocument doc = QJsonDocument::fromJson(raw_json.toUtf8());
	QJsonObject json = doc.object();

	QStringList keys = json.keys();
	QJsonValue value;
	for (int i = 0; i < keys.length() && value.toString("") != statusName; i++)
		value = json[keys[i]];

	qDebug() << "value = " << value;

	// Now that we have selected the namespace, we can take the variables:
	QJsonValue primaryColorItem = value.toObject()["primaryColor"];
	QJsonValue backgroundColorItem = value.toObject()["backgroundColor"];

	QString primaryColor = primaryColorItem.toString();
	QString backgroundColor = backgroundColorItem.toString();

	css = css.replace("@primaryColor", primaryColor);
	css = css.replace("@backgroundColor", backgroundColor);

	return css;
}
