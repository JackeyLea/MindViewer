/////////////////////
/// \author JackeyLea
/// \date 2024-10-29
/// \note 解析数据包并填充数据至结构体
/////////////////////

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QThread>

#include "icd.h"
#include "retriver.h"
#include "simulator.h"

class DataParser : public QThread
{
    Q_OBJECT
public:
    DataParser();

    void setSource(DataSourceType type);

    /// 获取一包数据并等待显示
    /// \brief getPkg
    /// \return
    ///
    _eegPkt getPkg();

    /// 清空缓存区
    /// \brief clearBuff
    ///
    void clearBuff();

    void add2Buff(QByteArray ba);//仅供单元测试使用
    QByteArray getBuff();//仅供单元测试使用

    /// 跳过无效字节
    /// \brief skipInvalidByte
    ///
    void skipInvalidByte();

    /// 解析一个有效数据包，但是数据不一定有效
    /// \brief parsePkg
    ///
    int parsePkg(QByteArray ba, bool &raw, short &rawValue, _eegPkt &pkt);

    void run();

private:
    void sltRcvData(QByteArray ba);

private:
    QList<_eegPkt> m_pkgList;//解析后的结构体列表

    Retriver *m_comRetriver;
    Simulator *m_sim;

    QByteArray mBuff;//数据缓存区
    int m_noise;//噪声含量
    int m_total;//总数
    int m_loss;//丢失数
    int m_rawCnt;//原始包数
    int m_eegCnt;//EEG包数
    int m_heart;//心跳
};

#endif // DATAPARSER_H
