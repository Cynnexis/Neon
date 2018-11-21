#ifndef STATUS_H
#define STATUS_H

#include "theme.h"

#include <QColor>
#include <QObject>

class Status : public QObject
{
	Q_OBJECT
public:
	Status(QString name, QColor primaryColor, QColor backgroundColor, QObject* parent = nullptr);
	Status(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor,
		   QColor darkPrimaryColor, QColor darkBackgroundColor, QObject* parent = nullptr);

	/* GETTERS */

	QString getName() const;
	QColor getPrimaryColor(const Theme& theme) const;
	QColor getBackgroundColor(const Theme& theme) const;
	QColor getLightPrimaryColor() const;
	QColor getLightBackgroundColor() const;
	QColor getDarkPrimaryColor() const;
	QColor getDarkBackgroundColor() const;

	/* OVERLOAD */

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

public slots:

	/* SETTERS */

	void setName(const QString& name);
	void setPrimaryColor(const Theme& theme, const QColor& primaryColor);
	void setPrimaryColor(const QColor& primaryColor, const Theme& theme);
	void setBackgroundColor(const Theme& theme, const QColor& backgroundColor);
	void setBackgroundColor(const QColor& backgroundColor, const Theme& theme);
	void setLightPrimaryColor(const QColor& lightPrimaryColor);
	void setLightBackgroundColor(const QColor& lightBackgroundColor);
	void setDarkPrimaryColor(const QColor& darkPrimaryColor);
	void setDarkBackgroundColor(const QColor& darkBackgroundColor);

signals:

	void nameChanged(QString);
	void lightPrimaryColorChanged(QColor);
	void lightBackgroundColorChanged(QColor);
	void darkPrimaryColorChanged(QColor);
	void darkBackgroundColorChanged(QColor);

private:
	QString name;
	QColor lightPrimaryColor;
	QColor lightBackgroundColor;
	QColor darkPrimaryColor;
	QColor darkBackgroundColor;

	void initialize(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor,
					QColor darkPrimaryColor, QColor darkBackgroundColor);
};

#endif // STATUS_H
