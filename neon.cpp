#include "neon.h"

/* CONSTRUCTOR */

Neon::Neon(QWidget* target) : QProxyStyle() {
	int t = settings.value("neon_lib/theme", Theme::DARK).toInt();
	this->initialize(target, static_cast<Theme>(t));
}

Neon::Neon(Theme theme, QWidget* target) : QProxyStyle() {
	this->initialize(target, theme);
}

void Neon::initialize(QWidget* target, Theme theme) {
	Q_INIT_RESOURCE(neon_resources);

	this->target = target;
	this->setTheme(theme);

	statuses.append(new Status("NORMAL", QColor(0, 100, 255), QColor(215, 218, 224), QColor(0, 100, 255), QColor(33, 37, 43)));
	statuses.append(new Status("SUCCESS", QColor(130, 255, 28), QColor(215, 218, 224), QColor(130, 255, 28), QColor(33, 37, 43)));
	statuses.append(new Status("INFO", QColor(28, 232, 255), QColor(215, 218, 224), QColor(28, 232, 255), QColor(33, 37, 43)));
	statuses.append(new Status("WARNING", QColor(252, 138, 32), QColor(215, 218, 224), QColor(252, 138, 32), QColor(33, 37, 43)));
	statuses.append(new Status("DANGER", QColor(252, 39, 32), QColor(215, 218, 224), QColor(252, 39, 32), QColor(33, 37, 43)));
	loadStatuses();

	indexCurrentStatus = settings.value("neon_lib/indexCurrentStatus", 0).toInt();

	if (this->target == nullptr)
		qApp->setStyleSheet(getStylesheet());
	else
		target->setStyleSheet(getStylesheet());
}

void Neon::loadStatuses() {
	// Fetch the list of names of statuses
	QStringList names = settings.value("neon_lib/statusesName", QVariant(QStringList())).toStringList();

	// For each name...
	for (QString name : names) {
		// Fetch the JSON representation of the status
		QString statusJson = settings.value("neon_lib/status(" + name + ")", "").toString();

		// Try to convert the JSON content into a string
		try {
			Status s = Status::fromString(statusJson);

			// If the conversion worked, add the status to the main list
			statuses.append(&s);
		} catch (std::exception e) {
			// If the conversion failed, delete the key and ignore
			settings.remove("neon_lib/status(" + name + ")");
		}
	}
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

	QStringList names = settings.value("neon_lib/statusesName", QVariant(QStringList())).toStringList();
	names.append(status->getName());

	settings.setValue("neon_lib/statusesName", names);
	settings.setValue("neon_lib/status(" + status->getName() + ")", status->toString());

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

Status* Neon::getCurrentStatus() {
	return statuses.at(indexCurrentStatus);
}

void Neon::setTheme(Theme theme) {
	this->theme = theme;
	settings.setValue("neon_lib/theme", this->theme);
	emit themeChanged(this->theme);
}

Status* Neon::setCurrentStatus(const Status& status) {
	return setCurrentStatus(status.getName());
}

Status* Neon::setCurrentStatus(const int index) {
	if (0 <= index && index < statuses.length()) {
		indexCurrentStatus = index;
		settings.setValue("neon_lib/indexCurrentStatus", indexCurrentStatus);
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

QString Neon::getStylesheet(Theme theme, Status status) {
	switch (theme) {
		case Theme::LIGHT:
			return NResources::getNeonLightCSS(status);
		default:
			return NResources::getNeonDarkCSS(status);
	}
}

QString Neon::getStylesheet(Theme theme) {
	return getStylesheet(theme, *getCurrentStatus());
}

QString Neon::getStylesheet(Status status) {
	return getStylesheet(getTheme(), status);
}

QString Neon::getStylesheet() {
	return getStylesheet(getTheme(), *getCurrentStatus());
}
