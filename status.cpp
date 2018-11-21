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

QColor Status::getPrimaryColor(const Theme& theme) const {
	switch (theme) {
		case Theme::LIGHT:
			return getLightPrimaryColor();
		default:
			return getDarkPrimaryColor();
	}
}

QColor Status::getBackgroundColor(const Theme& theme) const {
	switch (theme) {
		case Theme::LIGHT:
			return getLightBackgroundColor();
		default:
			return getDarkBackgroundColor();
	}
}

void Status::setName(const QString& name) {
	this->name = name;
	emit nameChanged(this->name);
}

void Status::setPrimaryColor(const Theme& theme, const QColor& primaryColor) {
	switch (theme) {
		case Theme::LIGHT:
			return setLightPrimaryColor(primaryColor);
		default:
			return setDarkPrimaryColor(primaryColor);
	}
}

void Status::setPrimaryColor(const QColor& primaryColor, const Theme& theme) {
	setPrimaryColor(theme, primaryColor);
}

void Status::setBackgroundColor(const Theme& theme, const QColor& backgroundColor) {
	switch (theme) {
		case Theme::LIGHT:
			return setLightBackgroundColor(backgroundColor);
		default:
			return setDarkBackgroundColor(backgroundColor);
	}
}

void Status::setBackgroundColor(const QColor& backgroundColor, const Theme& theme) {
	setBackgroundColor(theme, backgroundColor);
}

QColor Status::getLightPrimaryColor() const {
	return this->lightPrimaryColor;
}

void Status::setLightPrimaryColor(const QColor& lightPrimaryColor) {
	this->lightPrimaryColor = lightPrimaryColor;
	emit lightPrimaryColorChanged(this->lightPrimaryColor);
}

QColor Status::getLightBackgroundColor() const {
	return this->lightBackgroundColor;
}

void Status::setLightBackgroundColor(const QColor& lightBackgroundColor) {
	this->lightBackgroundColor = lightBackgroundColor;
	emit lightBackgroundColorChanged(this->lightBackgroundColor);
}

QColor Status::getDarkPrimaryColor() const
{
	return darkPrimaryColor;
}

void Status::setDarkPrimaryColor(const QColor& darkPrimaryColor)
{
	this->darkPrimaryColor = darkPrimaryColor;
	emit darkPrimaryColorChanged(this->darkPrimaryColor);
}

QColor Status::getDarkBackgroundColor() const
{
	return darkBackgroundColor;
}

void Status::setDarkBackgroundColor(const QColor& darkBackgroundColor)
{
	this->darkBackgroundColor = darkBackgroundColor;
	emit darkBackgroundColorChanged(this->darkBackgroundColor);
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
