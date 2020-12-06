#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void sltParserCompleted();

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionGithub_triggered();

    void on_actionCapture_triggered();

    void on_actionSerialPort_triggered();

    void on_actionPause_triggered();

    void on_actionResume_triggered();

    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
