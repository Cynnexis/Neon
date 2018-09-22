#ifndef AUTOREFRESHPROGRESSBAR_H
#define AUTOREFRESHPROGRESSBAR_H

#include<iostream>
#include <QProgressBar>


class AutoRefreshProgressBar : public QProgressBar {

	Q_OBJECT

public:
	AutoRefreshProgressBar(QWidget* parent = nullptr, bool autoRefresh = true) :
		QProgressBar(parent) {
		this->setAutoRefresh(autoRefresh);
	}

	/* GETTER */

	bool getAutoRefresh() {
		return this->autoRefresh;
	}

public slots:
	void setValueWithRespectToAutoRefresh(int value) {
		if (this->getAutoRefresh()) {
			this->setValue(value);
		}
	}

	/* SETTER */

	void setAutoRefresh(bool autoRefresh) {
		this->autoRefresh = autoRefresh;
	}

private:
	bool autoRefresh = true;
};

#endif // AUTOREFRESHPROGRESSBAR_H
