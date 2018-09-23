#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>
#include <QMainWindow>

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
	void on_actionExit_triggered();
	void on_actionDefault_toggled(bool toggled);
	void on_actionNeon_toggled(bool toggled);

private:
	Ui::MainWindow *ui;
	QStyle* defaultStyle = nullptr;
	QActionGroup* ag_style;
	QActionGroup* ag_theme;
};

#endif // MAINWINDOW_H
