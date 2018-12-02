#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	neon = new Neon(Theme::LIGHT, this);

	// Initialization
	increment = -1;
	on_pb_incrementLabel_clicked();

	ui->cb_gender->addItems({"Male", "Female", "Agender", "Transgender", "Male Transgender", "Female Transgender", "Non-binary", "Genderqueer", "Third Gender", "Two-spirit", "I want to keep it secret"});
	ui->cb_pronouns->addItems({"he", "she", "they", "<name>", "ae", "fae", "e", "ey", "per", "ve", "xe", "ze", "zie"});
	
	ui->cb_country->addItems(getCountries());
	
	// Init the tree
	QFileSystemModel model;
	model.setRootPath("");
	model.setReadOnly(true);
	model.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
	ui->tr_dir->setModel(&model);
	ui->tr_dir->setRootIndex(model.index(QDir::currentPath()));
	ui->tr_dir->setColumnWidth(0, ui->tr_dir->width() / 3);
	
	// Load from settings
	ui->le_firstname->setText(settings.value("form/firstname", "").toString());
	ui->le_lastname->setText(settings.value("form/lastname", "").toString());
	ui->sp_age->setValue(settings.value("form/age", 18).toInt());
	ui->dt_birthday->setDateTime(settings.value("form/birthday", QDateTime()).toDateTime());
	ui->cb_gender->setCurrentIndex(settings.value("form/gender", 0).toInt());
	ui->cb_pronouns->setEditText(settings.value("form/pronoun", "").toString());
	ui->cb_country->setCurrentIndex(settings.value("form/country", 0).toInt());
	
	int like = settings.value("form/likeNeon", 0).toInt();
	
	switch (like) {
		case 1:
			ui->rb_like->setChecked(true);
			break;
		case 2:
			ui->rb_dislike->setChecked(true);
			break;
		default:
			ui->rb_love->setChecked(true);
			break;
	}
	
	ui->tb_comments->setHtml(settings.value("form/comments", "").toString());
}

MainWindow::~MainWindow() {
	delete ui;
}

QStringList MainWindow::getCountries() {
#ifdef QT_DEBUG
	QFile f("tests/Glow/res/txt/countries.txt");
#else
	QFile f(":/txt/countries");
#endif
	
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		cout << "Cannot open `countries.txt`" << endl;
		throw "Cannot open `countries.txt`";
	}
	
	QString raw_countries = f.readAll();
	QStringList countries = raw_countries.split(QRegularExpression("(\r\n|\r|\n)"));
	countries.removeDuplicates();
	countries.removeAll(QString(""));
	
	return countries;
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

void MainWindow::on_cb_enableTristate_toggled(bool checked) {
    ui->cb_tristate->setEnabled(checked);
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

void MainWindow::on_le_firstname_textChanged(const QString& arg1) {
	updatePronounExample();
}

void MainWindow::on_le_firstname_textEdited(const QString& arg1) {
	updatePronounExample();
}

void MainWindow::on_cb_activateFlat_toggled(bool checked) {
	ui->pb_flat->setEnabled(!checked);
}

void MainWindow::on_pb_saveForm_clicked() {
    settings.setValue("form/firstname", ui->le_firstname->text());
    settings.setValue("form/lastname", ui->le_lastname->text());
    settings.setValue("form/age", ui->sp_age->value());
    settings.setValue("form/birthday", ui->dt_birthday->dateTime());
    settings.setValue("form/gender", ui->cb_gender->currentIndex());
    settings.setValue("form/pronoun", ui->cb_pronouns->currentText());
    settings.setValue("form/country", ui->cb_country->currentIndex());
	
	int like = 0;
	if (ui->rb_love->isChecked())
		like = 0;
	else if (ui->rb_like->isChecked())
		like = 1;
	else if (ui->rb_dislike->isChecked())
		like = 2;
	
    settings.setValue("form/likeNeon", like);
    settings.setValue("form/comments", ui->tb_comments->toHtml());
	
	settings.sync();
	qDebug() << "Settings saved at " << settings.fileName();
	ui->statusBar->showMessage("Form saved!", 5 * 1000);
}

void MainWindow::on_actionExit_triggered() {
    qApp->exit();
}

void MainWindow::on_actionNeon_triggered() {
    ui->actionDefault->setChecked(false);
	neon->neonize(this);
}

void MainWindow::on_actionDefault_triggered() {
	ui->actionNeon->setChecked(false);
	neon->unneonize(this);
}

void MainWindow::on_actionAbout_Glow_triggered() {
    QMessageBox::about(this, "About Glow...", "Glow is an application to test GUI.");
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QMessageBox::aboutQt(this, "About Qt...");
}
