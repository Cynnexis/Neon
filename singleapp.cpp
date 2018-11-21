#include "singleapp.h"

SingleApp::SingleApp(QString filename, QString errorMessage, QObject* parent) {
	if (filename == "")
		filename = QApplication::applicationName();
}
