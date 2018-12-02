#include "nresources.h"

QString read(const QString& filename);
QString constructCSS(const QString& statusName, const QString& raw_json, QString css = "");
QColor rgbStringToColor(const QString& rgb);

QString NResources::getNeonDarkJSONPath() {
#ifdef QT_DEBUG
	return "res/css/neon_light.json";
#else
	return ":/css/neon_light";
#endif
}

QString NResources::getNeonLightJSONPath() {
#ifdef QT_DEBUG
	return "res/css/neon_dark.json";
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

QString NResources::merge(QString css, QMap<QString, QString> vars) {
	// Add some keys
	if (vars.contains("primaryColor")) {
		vars["tint(primaryColor, light)"] = rgbStringToColor(vars["primaryColor"]).lighter().name();
		vars["tint(primaryColor, dark)"] = rgbStringToColor(vars["primaryColor"]).darker().name();
	}
	
	if (vars.contains("backgroundColor")) {
		vars["tint(backgroundColor, light)"] = rgbStringToColor(vars["backgroundColor"]).lighter().name();
		vars["tint(backgroundColor, dark)"] = rgbStringToColor(vars["backgroundColor"]).darker().name();
	}
	
	for (QString key : vars.keys()) {
		rgbStringToColor(vars.value(key, ""));
		css = css.replace("@" + key, vars.value(key, ""));
	}

	return css;
}

/* PRIVATE FUNCTIONS */

QString read(const QString& filename) {
	QFile f(filename);

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		IOException("File not found").raise();

	QString result = f.readAll();
	f.close();

	return result;
}

QString constructCSS(const QString& statusName, const QString& raw_json, QString css) {
	if (css == "")
		css = NResources::getNeonBaseCSS();

	QMap<QString, QString> vars;

	QJsonDocument doc = QJsonDocument::fromJson(raw_json.toUtf8());
	QJsonObject json = doc.object();

	QStringList keys = json.keys();
	QJsonValue value;
	for (int i = 0; i < keys.length() && value.toString("") != statusName; i++)
		value = json[keys[i]];

	// Now that we have selected the namespace, we can take the variables:
	QJsonValue primaryColorItem = value.toObject()["primaryColor"];
	QJsonValue backgroundColorItem = value.toObject()["backgroundColor"];

	QJsonArray primaryColorArray = primaryColorItem.toArray();
	QJsonArray backgroundColorArray = backgroundColorItem.toArray();

	QString primaryColor = "rgb(";
	QString backgroundColor = "rgb(";

	for (int i = 0; i < primaryColorArray.size(); i++)
		primaryColor += (i > 0 ? ", " : "") +  QString::number(primaryColorArray[i].toInt());
	primaryColor += ")";

	for (int i = 0; i < backgroundColorArray.size(); i++)
		backgroundColor += (i > 0 ? ", " : "") +  QString::number(backgroundColorArray[i].toInt());
	backgroundColor += ")";

	vars["primaryColor"] = primaryColor;
	vars["backgroundColor"] = backgroundColor;

	return NResources::merge(css, vars);
}

QColor rgbStringToColor(const QString& rgb) {
	QRegularExpression rgb_pattern("(?:rgb\\(([0-9]+),\\s*([0-9]+),\\s*([0-9]+)\\)|rgba\\(([0-9]+),\\s*([0-9]+),\\s*([0-9]+),\\s*([0-9]+)\\)|\\#([a-fA-F0-9]{3}(?:[a-fA-F0-9]{3})?));?");
	QRegularExpressionMatch match = rgb_pattern.match(rgb);
	
	if (!match.isValid() || !match.hasMatch())
		throw "The expression \"" + rgb.toStdString() + "\" is not valid";
	
	if (match.captured(1) != "") {
		return QColor(
					match.captured(1).toInt(),
					match.captured(2).toInt(),
					match.captured(3).toInt()
					);
	}
	else if (match.captured(4) != "") {
		return QColor(
					match.captured(1).toInt(),
					match.captured(2).toInt(),
					match.captured(3).toInt(),
					match.captured(4).toInt()
					);
	}
	else if (match.captured(4) != "") {
		return QColor(
					match.captured(4).toInt(),
					match.captured(5).toInt(),
					match.captured(6).toInt(),
					match.captured(7).toInt()
					);
	}
	else if (match.captured(8) != "")
		return QColor(match.captured(8));
	else
		throw "No color found in \"" + rgb.toStdString() + "\"";
}
