#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include <iostream>

#include <QObject>
#include <QException>
#include <QDebug>

using namespace std;

class IOException : public QException
{
public:
	IOException(const IOException& error);
	IOException(const QString message, const IOException& error);
	IOException(const QString message);

	void raise() const override;
	IOException* clone() const override;

	/* GETTER */

	QString getMessage() const;

public slots:
	/* SETTER */

	void setMessage(const QString& value);

private:
	QString message;
};

#endif // IOEXCEPTION_H
