/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 串口处理函数
///
////////////////////////////////////////////

#ifndef RETRIVER_H
#define RETRIVER_H

#include <QDebug>
#include <QString>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QSerialPort>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QSerialPortInfo>

namespace Ui {
class Retriver;
}

class Retriver : public QWidget
{
    Q_OBJECT

public:
    explicit Retriver(QWidget *parent = nullptr);
    ~Retriver();

    void showWgt();
    void stopCOM();

signals:
    void sigNewPkg(QByteArray ba);

private slots:
    void receiveData();
    void on_btnOpenClose_clicked();
    void on_btnCance_clicked();

private:
    Ui::Retriver *ui;

    QSerialPort *com;

    bool isCOMOpen=false;
};

#endif // RETRIVER_H
