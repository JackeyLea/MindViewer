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
#include <QString>

#include "generator.h"
#include "iostream"
#include "sstream"

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
    void sltReceiveData(QByteArray ba);

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionGithub_triggered();

    void on_actionSerialPort_triggered();

    void on_actionTest_triggered();

    void on_actionSave_triggered();

    void on_actionHex_triggered(bool checked);

    void on_actionGraph_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    Generator *gen;
};
#endif // MAINWINDOW_H
