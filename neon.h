#ifndef NEON_H
#define NEON_H

#include "neon_global.h"
#include "status.h"
#include "theme.h"
#include "nresources.h"

#include <iostream>
#include <QProxyStyle>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSettings>

using namespace std;

class NEONSHARED_EXPORT Neon : public QProxyStyle
{
	Q_OBJECT

public:

	/* CONSTRUCTOR */

	Neon(QWidget* target);
	Neon(QWidget* target, Theme theme);

	/* NEON METHODS */

	void polish(QPalette& palette) override;
	void polish(QWidget* widget) override;
	void unpolish(QWidget* widget) override;
	int pixelMetric(PixelMetric metric,
					const QStyleOption* option,
					const QWidget* widget) const override;
	int styleHint(StyleHint hint,
				  const QStyleOption* option,
				  const QWidget* widget,
				  QStyleHintReturn* returnData) const override;
	void drawPrimitive(PrimitiveElement element,
					   const QStyleOption* option,
					   QPainter* painter,
					   const QWidget* widget) const override;
	void drawControl(ControlElement control,
					 const QStyleOption* option,
					 QPainter* painter,
					 const QWidget* widget) const override;

	bool addStatus(Status *status);
	bool addStatus(QString name, QColor primaryColor);
	bool addStatus(QString name, QColor primaryColor, QColor backgroundColor);
	bool addStatus(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor, QColor darkPrimaryColor, QColor darkBackgroundColor);
	Status* getStatus(int index);
	Status* getStatus(QString name);
	bool removeStatus(Status *status);
	void removeStatus(int index);
	void removeStatus(QString name);

	/* GETTERS */

	Theme getTheme() const;
	Status* getCurrentStatus();

	QString getStylesheet(Theme theme, Status status);
	QString getStylesheet(Theme theme);
	QString getStylesheet(Status status);
	QString getStylesheet();

public slots:

	/* SETTERS */

	void setTheme(Theme theme);
	Status* setCurrentStatus(const Status& status);
	Status* setCurrentStatus(const int index);
	Status* setCurrentStatus(const QString name);

signals:
	void themeChanged(Theme);
	void statusAdded(Status*);
	void statusRemoved();
	void currentStatusChanged(Status*);

private:	
	Theme theme;
	QWidget* target;
	QSettings settings;

	QList<Status*> statuses;
	int indexCurrentStatus;

	void initialize(QWidget* target, Theme theme);
	void loadStatuses();
};

#endif // NEON_H
