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

class NEONSHARED_EXPORT Neon : public /*QProxyStyle*/QObject
{
	Q_OBJECT

public:

	/* CONSTRUCTOR */

	Neon(QWidget* target = nullptr);
	Neon(const Theme& theme, QWidget* target = nullptr);

	/* NEON METHODS */

	void neonize(QWidget* target = nullptr);
	void unneonize(QWidget* target = nullptr);
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
	QWidget* getTarget() const;
	Status* getCurrentStatus();

	QString getStylesheet(Theme theme, Status status);
	QString getStylesheet(Theme theme);
	QString getStylesheet(Status status);
	QString getStylesheet();
	
public slots:
	
	/* SETTERS */
	
	void setTheme(Theme theme);
	void setTarget(QWidget* value);
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

	void initialize(QWidget* target, const Theme& theme);
	void loadStatuses();
};

#endif // NEON_H
