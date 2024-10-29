#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    /// 初始化信号槽
    /// \brief initConn
    ///
    void initConn();

private slots:

    /// 串口按钮响应
    /// \brief sltBtnCOM
    ///
    void sltBtnCOM();

    /// 仿真数据按钮响应
    /// \brief sltBtnSIM
    ///
    void sltBtnSIM();

    /// 打开本地文件按钮响应
    /// \brief sltBtnLocal
    ///
    void sltBtnLocal();

    /// 播放按钮响应
    /// \brief sltBtnPlay
    ///
    void sltBtnPlay();

    /// 暂停按钮响应
    /// \brief sltBtnPause
    ///
    void sltBtnPause();

    /// 清空按钮响应 清空界面数据和缓存区数据
    /// \brief sltBtnClear
    ///
    void sltBtnClear();

    /// 保存按钮响应 保存串口收到的数据
    /// \brief sltBtnSave
    ///
    void sltBtnSave();

private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H
