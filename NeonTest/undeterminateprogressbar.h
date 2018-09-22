#ifndef UNDETERMINATEPROGRESSBAR_H
#define UNDETERMINATEPROGRESSBAR_H

#include <QProgressBar>


class UndeterminateProgressBar : public QProgressBar {

	Q_OBJECT

public:
	UndeterminateProgressBar(QWidget* parent = nullptr) : QProgressBar(parent) {
		setUndeterminate(true);
	}

public slots:
	void setUndeterminate(bool undeterminate) {
		if (undeterminate) {
			this->setMinimum(0);
			this->setMaximum(0);
			this->setValue(0);
		}
		else {
			this->setMinimum(0);
			this->setMaximum(100);
			this->setValue(50);
		}
	}
};

#endif // UNDETERMINATEPROGRESSBAR_H
