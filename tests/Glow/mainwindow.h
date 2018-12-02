#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QObject>
#include <QString>
#include <QMainWindow>
#include <QSettings>
#include <QDateTime>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <Neon>
#include <nresources.h>

using namespace std;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
	QStringList getCountries();

private slots:
	void on_pushButton_clicked();
	void on_cb_activateFlat_toggled(bool checked);
	void on_pb_incrementLabel_clicked();
	void on_cb_enableTristate_toggled(bool checked);

	void on_rb_pb_indeterminate_toggled(bool checked);
	void on_rb_pb_specificValue_toggled(bool checked);
	void on_sl_pbValue_rangeChanged(int min, int max);
	void on_sl_pbValue_valueChanged(int value);
	
	void on_cb_pronouns_currentTextChanged(const QString &arg1);
	void on_le_firstname_textChanged(const QString &arg1);
	void on_le_firstname_textEdited(const QString &arg1);
	void on_pb_saveForm_clicked();
	
	void on_actionExit_triggered();
	void on_actionNeon_triggered();
	void on_actionDefault_triggered();
	void on_actionAbout_Glow_triggered();
	void on_actionAbout_Qt_triggered();
	
private:
	Ui::MainWindow *ui;
	QSettings settings;
	Neon* neon;

	int increment;

	void updatePronounExample();
};

#endif // MAINWINDOW_H
