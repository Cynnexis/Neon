#include "status.h"

Status::Status(QString name, QColor primaryColor, QColor backgroundColor, QObject* parent) : QObject(parent) {
	initialize(name, primaryColor, backgroundColor, primaryColor, backgroundColor);
}

Status::Status(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor, QColor darkPrimaryColor, QColor darkBackgroundColor, QObject* parent) : QObject(parent) {
	initialize(name, lightPrimaryColor, lightBackgroundColor, darkPrimaryColor, darkBackgroundColor);
}

Status::Status(QString name, QMap<Theme, QColor> primaryColors, QMap<Theme, QColor> backgroundColors) {
	initialize(name, primaryColors[Theme::LIGHT], backgroundColors[Theme::LIGHT], primaryColors[Theme::DARK], backgroundColors[Theme::DARK]);
}

Status::Status(const Status& copy) {
	initialize(copy.getName(), copy.getLightPrimaryColor(), copy.getLightBackgroundColor(), copy.getDarkPrimaryColor(), copy.getDarkBackgroundColor());
}

Status::~Status() {
	//
}

void Status::initialize(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor, QColor darkPrimaryColor, QColor darkBackgroundColor) {
	setName(name);
	setLightPrimaryColor(lightPrimaryColor);
	setLightBackgroundColor(lightBackgroundColor);
	setDarkPrimaryColor(darkPrimaryColor);
	setDarkBackgroundColor(darkBackgroundColor);
}

/* GETTERS & SETTERS */

QString Status::getName() const {
	return this->name;
}

QMap<Theme, QColor> Status::getPrimaryColors() const {
	return this->primaryColors;
}

QMap<Theme, QColor> Status::getBackgroundColors() const {
	return this->backgroundColors;
}

void Status::setName(const QString& name) {
	this->name = name;
	emit nameChanged(this->name);
}

QColor Status::getPrimaryColor(const Theme& theme) const {
	return this->primaryColors[theme];
}

void Status::setPrimaryColor(const Theme& theme, const QColor& primaryColor) {
	this->primaryColors[theme] = primaryColor;
	emit primaryColorChanged(theme, primaryColor);
}

void Status::setPrimaryColor(const QColor& primaryColor, const Theme& theme) {
	setPrimaryColor(theme, primaryColor);
}

QColor Status::getBackgroundColor(const Theme& theme) const {
	return this->backgroundColors[theme];
}

void Status::setBackgroundColor(const Theme& theme, const QColor& backgroundColor) {
	this->backgroundColors[theme] = backgroundColor;
	emit backgroundColorChanged(theme, backgroundColor);
}

void Status::setBackgroundColor(const QColor& backgroundColor, const Theme& theme) {
	setBackgroundColor(theme, backgroundColor);
}

QColor Status::getLightPrimaryColor() const {
	return getPrimaryColor(Theme::LIGHT);
}

void Status::setLightPrimaryColor(const QColor& lightPrimaryColor) {
	setPrimaryColor(Theme::LIGHT, lightPrimaryColor);
}

QColor Status::getLightBackgroundColor() const {
	return getBackgroundColor(Theme::LIGHT);
}

void Status::setLightBackgroundColor(const QColor& lightBackgroundColor) {
	setBackgroundColor(Theme::LIGHT, lightBackgroundColor);
}

QColor Status::getDarkPrimaryColor() const {
	return getPrimaryColor(Theme::DARK);
}

void Status::setDarkPrimaryColor(const QColor& darkPrimaryColor) {
	setPrimaryColor(Theme::DARK, darkPrimaryColor);
}

QColor Status::getDarkBackgroundColor() const {
	return getBackgroundColor(Theme::DARK);
}

/* IO Functions */

QString Status::toString() {
	QJsonObject json;

	json["name"] = getName();

	QJsonObject jPrimaryColors;
	for (Theme key : primaryColors.keys())
		jPrimaryColors[QString::number(key)] = primaryColors[key].name();

	json["primaryColors"] = jPrimaryColors;

	QJsonObject jBackgroundColors;
	for (Theme key : backgroundColors.keys())
		jBackgroundColors[QString::number(key)] = backgroundColors[key].name();

	json["backgroundColors"] = jBackgroundColors;

	QJsonDocument doc(json);
	return doc.toJson(QJsonDocument::Compact);
}

Status Status::fromString(QString string) {
	QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
	QJsonObject json = doc.object();

	QString name = "";
	QMap<Theme, QColor> primaryColors;
	QMap<Theme, QColor> backgroundColors;

	name = json["name"].toString("");

	if (name == "")
		throw "Cannot parse \"" + string.toStdString() + "\" to get a Status.";

	QJsonObject jPrimaryColors = json["primaryColors"].toObject();
	for (QString key : jPrimaryColors.keys())
		primaryColors[static_cast<Theme>(key.toInt())] = QColor(jPrimaryColors[key].toString());

	QJsonObject jBackgroundColors = json["primaryColors"].toObject();
	for (QString key : jBackgroundColors.keys())
		backgroundColors[static_cast<Theme>(key.toInt())] = QColor(jBackgroundColors[key].toString());

	return Status(name, primaryColors, backgroundColors);
}

void Status::setDarkBackgroundColor(const QColor& darkBackgroundColor) {
	setBackgroundColor(Theme::DARK, darkBackgroundColor);
}

/* OVERLOAD */

bool Status::operator==(const Status& other) const {
	return this->getName() == other.getName() &&
			this->getPrimaryColors() == other.getPrimaryColors() &&
			this->getBackgroundColors() == other.getBackgroundColors();
}

bool Status::operator!=(const Status& other) const {
	return !(*this == other);
}
