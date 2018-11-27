#include "ioexception.h"

IOException::IOException(const IOException& error) : QException(error) {
	setMessage("");
}
IOException::IOException(const QString message, const IOException& error) : QException(error) {
	setMessage(message);
}
IOException::IOException(const QString message) : QException() {
	setMessage(message);
}

void IOException::raise() const {
	cout << message.toStdString() << endl;;
	throw *this;
}

IOException* IOException::clone() const {
	return new IOException(*this);
}

QString IOException::getMessage() const {
	return message;
}

void IOException::setMessage(const QString& value) {
	message = value;
}
