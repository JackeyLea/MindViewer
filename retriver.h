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
    /// 构造函数
    /// \brief Retriver
    /// \param parent
    ///
    explicit Retriver(QWidget *parent = nullptr);

    ///
    /// 释放资源
    ~Retriver();

    /// 显示本类界面
    /// \brief showWgt
    ///
    void showWgt();

    /// 关闭通道
    /// \brief stopCOM
    ///
    void stopCOM();

signals:
    /// 通知解析器有新包
    /// \brief sigNewPkg
    /// \param ba
    ///
    void sigNewPkg(QByteArray ba);

private slots:
    /// 处理从COM口过来的数据
    /// \brief receiveData
    ///
    void receiveData();

    /// 打开关闭串口
    /// \brief on_btnOpenClose_clicked
    ///
    void on_btnOpenClose_clicked();

    /// 取消操作
    /// \brief on_btnCance_clicked
    ///
    void on_btnCance_clicked();

private:
    Ui::Retriver *ui;

    //串口操作
    QSerialPort *com;

    bool isCOMOpen=false;
};

#endif // RETRIVER_H
