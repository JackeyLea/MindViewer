/////////////////////
/// \author JackeyLea
/// \date 2024-10-29
/// \note 解析数据包并填充数据至结构体
/////////////////////

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "icd.h"
#include "retriver.h"
#include "simulator.h"

class DataParser : public QThread
{
    Q_OBJECT
public:
    DataParser();
    ~DataParser();

    void setFilePath(QString path);

    void setSource(DataSourceType type);

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
    int parsePkg(QByteArray ba, bool &raw, _eegPkt &pkt);

    void run();

signals:
    void sigNewPkt(_eegPkt pkt);

private slots:
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
    QVector<double> m_rawData;//原始数据

    QMutex m_mutex;

    QString m_filePath;
};

#endif // DATAPARSER_H
