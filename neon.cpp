#include "neon.h"

/* CONSTRUCTOR */

Neon::Neon() : QProxyStyle("") {
	qDebug() << NResources::getNeonDarkJSONPath();
}

Neon::Neon(QStyle *style, Theme theme, QWidget* target) : QProxyStyle(style) {
	this->initialize(theme);
}

Neon::Neon(const QString &key, Theme theme, QWidget* target) : QProxyStyle(key) {
	this->initialize(theme);
}

void Neon::initialize(Theme theme) {
	Q_INIT_RESOURCE(neon_resources);

	statuses.append(new Status("NORMAL", QColor(0, 100, 255), QColor(215, 218, 224), QColor(0, 100, 255), QColor(33, 37, 43)));
	statuses.append(new Status("SUCCESS", QColor(130, 255, 28), QColor(215, 218, 224), QColor(130, 255, 28), QColor(33, 37, 43)));
	statuses.append(new Status("INFO", QColor(28, 232, 255), QColor(215, 218, 224), QColor(28, 232, 255), QColor(33, 37, 43)));
	statuses.append(new Status("WARNING", QColor(252, 138, 32), QColor(215, 218, 224), QColor(252, 138, 32), QColor(33, 37, 43)));
	statuses.append(new Status("DANGER", QColor(252, 39, 32), QColor(215, 218, 224), QColor(252, 39, 32), QColor(33, 37, 43)));

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

bool Neon::addStatus(Status* status) {
	for (const Status* s : this->statuses)
		if (s == status || s->getName() == status->getName())
			return false;

	this->statuses.append(status);
	return true;
}

bool Neon::addStatus(QString name, QColor primaryColor) {
	Status* normal = getStatus("NORMAL");
	return addStatus(new Status(name, primaryColor, normal->getLightBackgroundColor(),
								primaryColor, normal->getDarkBackgroundColor()));
}

bool Neon::addStatus(QString name, QColor primaryColor, QColor backgroundColor) {
	return addStatus(new Status(name, primaryColor, backgroundColor,
								primaryColor, backgroundColor));
}

bool Neon::addStatus(QString name, QColor lightPrimaryColor, QColor lightBackgroundColor, QColor darkPrimaryColor, QColor darkBackgroundColor) {
	return addStatus(new Status(name, lightPrimaryColor, lightBackgroundColor,
								darkPrimaryColor, darkBackgroundColor));
}

Status* Neon::getStatus(int index) {
	return this->statuses.at(index);
}

Status* Neon::getStatus(QString name) {
	for (Status* s : this->statuses)
		if (s->getName() == name)
			return s;

	return nullptr;
}

bool Neon::removeStatus(Status* status) {
	return this->statuses.removeOne(status);
}

void Neon::removeStatus(int index) {
	if (index >= 5)
		this->statuses.removeAt(index);
	else
		throw std::invalid_argument("Cannot remove built-in statuses. Please enter an index greater than 5.");
}

void Neon::removeStatus(QString name) {
	if (name != "NORMAL" || name != "SUCCESS" || name != "INFO" || name != "WARNING" || name != "DANGER") {
		for (int i = 0; i < this->statuses.size(); i++) {
			if (this->statuses.at(i)->getName() == name) {
				removeStatus(i);
				break;
			}
		}

		// If the old index was pointing at the old status, change it to "NORMAL"
		setCurrentStatus(0);
	}
}

/* GETTER & SETTER */

Theme Neon::getTheme() const {
	return this->theme;
}

void Neon::setTheme(Theme theme) {
	this->theme = theme;
}

Status* Neon::setCurrentStatus(const Status& status) {
	return setCurrentStatus(status.getName());
}

Status* Neon::setCurrentStatus(const int index) {
	if (0 <= index && index < statuses.length()) {
		indexCurrentStatus = index;
		emit currentStatusChanged(statuses[indexCurrentStatus]);
	}

	return statuses[indexCurrentStatus];
}

Status* Neon::setCurrentStatus(const QString name) {
	for (int i = 0; i < this->statuses.size(); i++)
		if (this->statuses.at(i)->getName() == name)
			return setCurrentStatus(i);

	return statuses[indexCurrentStatus];
}
