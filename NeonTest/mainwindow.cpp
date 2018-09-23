#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <neon.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	defaultStyle = QApplication::style();
	ag_style = new QActionGroup(this);
	ag_theme = new QActionGroup(this);

	ag_style->addAction(ui->actionDefault);
	ag_style->addAction(ui->actionNeon);

	ag_theme->addAction(ui->actionDark);
	ag_theme->addAction(ui->actionLight);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_actionExit_triggered() {
	QApplication::exit();
}

void MainWindow::on_actionDefault_toggled(bool toggled) {
	if (toggled) {
		QApplication::setStyle(this->defaultStyle);
		ui->menuTheme->setEnabled(false);
	}
}

void MainWindow::on_actionNeon_toggled(bool toggled) {
	if (toggled) {
		QApplication::setStyle(new Neon());
		ui->menuTheme->setEnabled(true);
	}
}
