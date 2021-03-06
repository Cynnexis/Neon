#include "neon.h"

/* CONSTRUCTOR */

Neon::Neon(QWidget* target) : QObject(target) {
	int t = settings.value("neon_lib/theme", Theme::DARK).toInt();
	this->initialize(target, static_cast<Theme>(t));
}

Neon::Neon(const Theme& theme, QWidget* target) : QObject(target) {
	this->initialize(target, theme);
}

void Neon::initialize(QWidget* target, const Theme& theme) {
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
	
	//neonize(this->target);
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

void Neon::neonize(QWidget* target) {
	setTarget(target);
	
	/*QGraphicsDropShadowEffect shadowEffect;
	shadowEffect.setOffset(0, 0);
	shadowEffect.setBlurRadius(10);
	shadowEffect.setColor(this->getCurrentStatus()->getPrimaryColor(this->getTheme()));*/
	
	if (this->target == nullptr) {
		qApp->setStyleSheet(getStylesheet());
		//applyEffectOnTree(target, shadowEffect);
	}
	else {
		target->setStyleSheet(getStylesheet());
		//applyEffectOnTree(target, shadowEffect);
	}
}

void Neon::neonize(QGuiApplication* target) {
	if (target != nullptr) {
		for (QObject* child : target->children()) {
			try {
				QWidget* w_child = qobject_cast<QWidget*>(child);
				
				if (w_child != nullptr)
					neonize(w_child);
			} catch (std::exception e) {}
		}
	}
	else
		this->neonize();
}

void Neon::unneonize(QWidget* target) {
	if (target == nullptr)
		qApp->setStyleSheet("");
	else
		target->setStyleSheet("");
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

void Neon::processNodes(QObject* tree, void (*f)(QObject*)) {
	for (QObject* child : tree->children()) {
		f(child);
		processNodes(child, f);
	}
}

void Neon::applyEffectOnTree(QWidget* target, QGraphicsEffect& effect) {
	target->setGraphicsEffect(&effect);
	
	for (QObject* child : target->children()) {
		try {
			QWidget* w_child = qobject_cast<QWidget*>(child);
			
			if (w_child != nullptr)
				applyEffectOnTree(w_child, effect);
		} catch (std::exception e) {}
	}
}

void Neon::applyEffectOnTree(QGuiApplication* target, QGraphicsEffect& effect) {
	for (QObject* child : target->children()) {
		try {
			QWidget* w_child = qobject_cast<QWidget*>(child);
			
			if (w_child != nullptr)
				applyEffectOnTree(w_child, effect);
		} catch (std::exception e) {}
	}
}

template<class Widget>
void Neon::applyEffectOnTreeOnType(QWidget* target, QGraphicsEffect& effect) {
	target->setGraphicsEffect(&effect);
	
	for (QObject* child : target->children()) {
		try {
			QWidget* w_child = qobject_cast<Widget*>(child);
			
			if (w_child != nullptr)
				applyEffectOnTreeOnType<Widget>(w_child, effect);
		} catch (std::exception e) {}
	}
}

template<class... Widgets>
void Neon::applyEffectOnTreeOnTypes(QWidget* target, QGraphicsEffect& effect) {
	int parameters[] = {0, (applyEffectOnTreeOnType<Widgets>(target, effect), 0)...};
	(void)parameters;
}

/* GETTER & SETTER */

Theme Neon::getTheme() const {
	return this->theme;
}

void Neon::setTheme(Theme theme) {
	this->theme = theme;
	settings.setValue("neon_lib/theme", this->theme);
	emit themeChanged(this->theme);
}

QWidget* Neon::getTarget() const {
	return target;
}

void Neon::setTarget(QWidget* value) {
	target = value;
}

Status* Neon::getCurrentStatus() {
	return statuses.at(indexCurrentStatus);
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
