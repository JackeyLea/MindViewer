////////////////////////
/// \author JackeyLea
/// \date 2024-10-29
/// \brief 单元测试类
////////////////////////

#ifndef MINDVIEWERTEST_H
#define MINDVIEWERTEST_H

#include <QObject>
#include <QtTest/QTest>

class MindViewerTest : public QObject
{
    Q_OBJECT

private slots:
    /// 检测模拟部分 //////////////

    /// 检测模拟生成原始数据包
    /// \brief case_checkGetRaw
    ///
    void case_checkGetRaw();

    /// 检测模拟生成EEG数据包
    /// \brief case_checkGetEEG
    ///
    void case_checkGetEEG();

    /// 检测能否正常跳过无效数据
    /// \brief case_checkSkip
    ///
    void case_checkSkip();
    void case_checkSkip1();
    void case_checkSkip2();
};

#endif // MINDVIEWERTEST_H
