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
    /// 构造函数
    /// \brief Simulator
    ///
    Simulator();

    ///
    /// 释放资源
    ~Simulator();

    /// 生成一个模块包
    /// \brief getOne
    /// \param mn 模块号
    /// \param max 数值上限，下限默认为0
    /// \return
    ///
    QByteArray getOne(uchar ucModelIndex, int iMax);

    /// 模拟原始数据包
    /// \brief getRaw
    /// \param bNoise
    /// \return
    ///
    QByteArray getRaw(bool bNoise=false);

    /// 模拟EEG数据包
    /// \brief getEEG
    /// \param noise
    /// \return
    ///
    QByteArray getEEG(bool bNoise=false);

signals:
    /// 通知界面已经成功解析一包
    /// \brief sigNewPkg
    /// \param ba
    ///
    void sigNewPkg(QByteArray ba);

private:
    QTimer *m_pTimer;

    uint m_unIterCnt;
};

#endif // SIMULATOR_H
