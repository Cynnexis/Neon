#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QString>
#include <QMainWindow>
#include <neon.h>
#include <nresources.h>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

	void on_rb_pb_indeterminate_toggled(bool checked);
	void on_rb_pb_specificValue_toggled(bool checked);
	void on_sl_pbValue_rangeChanged(int min, int max);
	void on_sl_pbValue_valueChanged(int value);
	void on_pb_incrementLabel_clicked();
	void on_cb_pronouns_currentTextChanged(const QString &arg1);
	void on_le_firstname_textChanged(const QString &arg1);
	void on_le_firstname_textEdited(const QString &arg1);

private:
	Ui::MainWindow *ui;

	int increment;

	void updatePronounExample();
};

#endif // MAINWINDOW_H
