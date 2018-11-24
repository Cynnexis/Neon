#include "status.h"

Status::Status(QString name, QColor primaryColor, QColor backgroundColor, QObject* parent) : QObject(parent) {
	initialize(name, primaryColor, backgroundColor, primaryColor, backgroundColor);
}

Status::Status(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor, QColor darkPrimaryColor, QColor darkBackgroundColor, QObject* parent) : QObject(parent) {
	initialize(name, lightPrimaryColor, lightBackgroundColor, darkPrimaryColor, darkBackgroundColor);
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

void Status::setDarkBackgroundColor(const QColor& darkBackgroundColor) {
	setBackgroundColor(Theme::DARK, darkBackgroundColor);
}

/* OVERLOAD */

bool Status::operator==(const Status& other) const {
	return this->getName() == other.getName() &&
			this->getLightPrimaryColor() == other.getLightPrimaryColor() &&
			this->getLightBackgroundColor() == other.getLightBackgroundColor() &&
			this->getDarkPrimaryColor() == other.getDarkPrimaryColor() &&
			this->getDarkBackgroundColor() == other.getDarkBackgroundColor();
}

bool Status::operator!=(const Status& other) const {
	return !(*this == other);
}
