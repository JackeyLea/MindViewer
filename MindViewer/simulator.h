/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 用于产生测试数据
///
////////////////////////////////////////////

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QVector>

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator();
    ~Simulator();

    /// 生成一个模块包
    /// \brief getOne
    /// \param mn 模块号
    /// \param max 数值上限，下限默认为0
    /// \return
    ///
    QByteArray getOne(uchar mn, int max);

    /// 模拟原始数据包
    /// \brief getRaw
    /// \param noise
    /// \return
    ///
    QByteArray getRaw(bool noise=false);

    /// 模拟EEG数据包
    /// \brief getEEG
    /// \param noise
    /// \return
    ///
    QByteArray getEEG(bool noise=false);

signals:
    /// 通知界面已经成功解析一包
    /// \brief sigNewPkg
    /// \param ba
    ///
    void sigNewPkg(QByteArray ba);

private:
    QTimer *timer;

    int i=0;
};

#endif // SIMULATOR_H
