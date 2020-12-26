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
#include <QPen>
#include <QResizeEvent>

#include "generator.h"
#include "retriver.h"
#include "common.h"

/* Parser types */
#define PARSER_TYPE_NULL       0x00
#define PARSER_TYPE_PACKETS    0x01    /* Stream bytes as ThinkGear Packets */
#define PARSER_TYPE_2BYTERAW   0x02    /* Stream bytes as 2-byte raw data */

/* Data CODE definitions */
#define PARSER_CODE_BATTERY            0x01
#define PARSER_CODE_POOR_QUALITY       0x02
#define PARSER_CODE_ATTENTION          0x04
#define PARSER_CODE_MEDITATION         0x05
#define PARSER_CODE_8BITRAW_SIGNAL     0x06
#define PARSER_CODE_RAW_MARKER         0x07

#define PARSER_CODE_RAW_SIGNAL         0x80
#define PARSER_CODE_EEG_POWERS         0x81
#define PARSER_CODE_ASIC_EEG_POWER_INT 0x83

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int parserData(QByteArray ba, bool &raw, short &rawValue, bool &eeg, struct _eegPkt &pkt);

protected:
    void resizeEvent(QResizeEvent *);

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
    Retriver *retriverWgt;
};
#endif // MAINWINDOW_H
