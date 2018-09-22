#include "neon.h"

/* CONSTRUCTOR */

Neon::Neon(Theme theme) : QProxyStyle() {
	this->setTheme(theme);
}

/* NEON METHODS */

void Neon::polish(QPalette& palette) {
	//
}

void Neon::polish(QWidget* widget) {
	//
}

void Neon::unpolish(QWidget* widget) {
	//
}

int Neon::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option,
					  const QWidget* widget) const {
	return 0;
}

int Neon::styleHint(QStyle::StyleHint hint, const QStyleOption* option,
					const QWidget* widget, QStyleHintReturn* returnData) const {
	return 0;
}

void Neon::drawPrimitive(QStyle::PrimitiveElement element,
						 const QStyleOption* option, QPainter* painter,
						 const QWidget* widget) const {
	//
}

void Neon::drawControl(QStyle::ControlElement control,
					   const QStyleOption* option, QPainter* painter,
					   const QWidget* widget) const {
	//
}

/* GETTER & SETTER */

Theme Neon::getTheme() const {
	return this->theme;
}

void Neon::setTheme(Theme theme) {
	this->theme = theme;
}


