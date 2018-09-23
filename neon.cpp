#include "neon.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

/* CONSTRUCTOR */

Neon::Neon(QStyle *style, Theme theme) : QProxyStyle(style) {
	this->initialize(theme);
}

Neon::Neon(const QString &key, Theme theme) : QProxyStyle(key) {
	this->initialize(theme);
}

void Neon::initialize(Theme theme) {
	Q_INIT_RESOURCE(neon_resources);
	QFile f_style(":/css/neon_darkness");

	if (!f_style.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QString error(tr("Cannot read the QSS (Qt Style Sheet)."));
		QMessageBox::critical(nullptr, "Error", error);
		cout << "Neon::initialize> Error: " << error.toStdString() << endl;
		qApp->exit(-1);
	}

	QTextStream in(&f_style);

	QString stylesheetContent("");
	while (!in.atEnd())
		stylesheetContent += in.readLine();

	f_style.close();

	cout << "Neon::initialize> stylesheet: " << stylesheetContent.toStdString() << endl;
	qApp->setStyleSheet(stylesheetContent);
	this->setTheme(theme);
}

/* NEON METHODS */

void Neon::polish(QPalette& palette) {
	this->QProxyStyle::polish(palette);
}

void Neon::polish(QWidget* widget) {
	this->QProxyStyle::polish(widget);
}

void Neon::unpolish(QWidget* widget) {
	this->QProxyStyle::unpolish(widget);
}

int Neon::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option,
					  const QWidget* widget) const {
	return this->QProxyStyle::pixelMetric(metric, option, widget);
}

int Neon::styleHint(QStyle::StyleHint hint, const QStyleOption* option,
					const QWidget* widget, QStyleHintReturn* returnData) const {
	return this->QProxyStyle::styleHint(hint, option, widget, returnData);
}

void Neon::drawPrimitive(QStyle::PrimitiveElement element,
						 const QStyleOption* option, QPainter* painter,
						 const QWidget* widget) const {
	return this->QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void Neon::drawControl(QStyle::ControlElement control,
					   const QStyleOption* option, QPainter* painter,
					   const QWidget* widget) const {
	return this->QProxyStyle::drawControl(control, option, painter, widget);
}

/* GETTER & SETTER */

Theme Neon::getTheme() const {
	return this->theme;
}

void Neon::setTheme(Theme theme) {
	this->theme = theme;
}



