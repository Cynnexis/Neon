#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	//Neon neon;

	// Initialization
	increment = -1;
	on_pb_incrementLabel_clicked();

	ui->cb_gender->addItems(QStringList({"Male", "Female", "Agender", "Transgender", "Male Transgender", "Female Transgender", "Non-binary", "Genderqueer", "Third Gender", "Two-spirit"}));
	ui->cb_pronouns->addItems(QStringList({"he", "she", "they", "<name>", "ae", "fae", "e", "ey", "per", "ve", "xe", "ze", "zie"}));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pushButton_clicked() {
	QMessageBox::information(this, "Important Information", "Attention: Information Available.\n\nYou must patch the telephone device back to the console unit.");
}

void MainWindow::on_rb_pb_indeterminate_toggled(bool checked) {
	if (checked) {
		ui->sl_pbValue->setEnabled(false);
		ui->pb_custom->setMinimum(0);
		ui->pb_custom->setMaximum(0);
		ui->pb_custom->setValue(-1);
	}
}

void MainWindow::on_rb_pb_specificValue_toggled(bool checked) {
	if (checked) {
		ui->sl_pbValue->setEnabled(true);
		ui->pb_custom->setMinimum(ui->sl_pbValue->minimum());
		ui->pb_custom->setMaximum(ui->sl_pbValue->maximum());
		ui->pb_custom->setValue(ui->sl_pbValue->value());
	}
}

void MainWindow::on_sl_pbValue_rangeChanged(int min, int max) {
	if (ui->rb_pb_specificValue->isChecked()) {
		ui->pb_custom->setMinimum(min);
		ui->pb_custom->setMaximum(max);
		ui->pb_custom->setValue(ui->sl_pbValue->value());
	}
}

void MainWindow::on_sl_pbValue_valueChanged(int value) {
	if (ui->rb_pb_specificValue->isChecked())
		ui->pb_custom->setValue(value);
}

void MainWindow::on_pb_incrementLabel_clicked() {
	ui->lb_increment->setText(tr("You clicked onto this button %n time(s).", "", ++increment));
}

void MainWindow::on_cb_pronouns_currentTextChanged(const QString& arg1) {
	updatePronounExample();
}

void MainWindow::updatePronounExample() {
	QString name = ui->le_firstname->text();
	QString pronoun = ui->cb_pronouns->currentText();

	if (pronoun == "<name>")
		pronoun = name;

	if (name != "" && pronoun != "") {
		char buffer[528];
		sprintf(buffer, tr("- Have you seen %s?\n- Yes, %s %s in this neon restaurant over there.").toStdString().c_str(),
				name.toStdString().c_str(), pronoun.toStdString().c_str(), pronoun != "they" ? "is" : "are");
		ui->lb_pronounExample->setText(buffer);
	}
	else
		ui->lb_pronounExample->setText("Please fill `first name` and `pronoun` fields first");
}

void MainWindow::on_le_firstname_textChanged(const QString &arg1) {
	updatePronounExample();
}

void MainWindow::on_le_firstname_textEdited(const QString &arg1) {
	updatePronounExample();
}
