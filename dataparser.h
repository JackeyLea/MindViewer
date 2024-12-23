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
#include "localfile.h"

class DataParser : public QThread
{
    Q_OBJECT
public:
    /// 构造函数
    /// \brief DataParser
    ///
    DataParser();

    ///
    /// 释放资源
    ~DataParser();

    /// 设置保存数据至本地
    /// \brief saveLocalFile
    ///
    void saveLocalFile();

    /// 设置文件路径
    /// \brief setFilePath
    /// \param path
    ///
    void setFilePath(const QString& path);

    /// 设置数据源类型
    /// \brief setSource
    /// \param type
    ///
    void setSource(DataSourceType type);

    /// 清空缓存区
    /// \brief clearBuff
    ///
    void clearBuff();

protected:

    /// 跳过无效字节
    /// \brief skipInvalidByte
    ///
    void skipInvalidByte();

    /// 解析一个有效数据包，但是数据不一定有效
    /// \brief parsePkg
    ///
    int parsePkg(const QByteArray& ba, bool &raw, _eegPkt &pkt);

    /// 独立线程函数
    /// \brief run
    ///
    void run();

signals:
    /// 通知界面有新数据包
    /// \brief sigNewPkt
    /// \param pkt
    ///
    void sigNewPkt(_eegPkt pkt);

private slots:
    /// 接收从数据源发过来的数据并填充至解析缓存区
    /// \brief sltRcvData
    /// \param ba
    ///
    void sltRcvData(QByteArray strData);

private:
    /// 数据源
    Retriver *m_pCOMRetriver;
    Simulator *m_pSIM;
    LocalFile *m_pLocalFile;

    QByteArray m_strBuff;//数据缓存区
    uint m_uiNoise;//噪声含量
    uint m_uiTotal;//总数
    uint m_uiLoss;//丢失数
    uint m_uiRawCnt;//原始包数
    uint m_uiEEGCnt;//eeg数据包数
    QVector<double> m_vRawData;//原始数据

    QMutex m_mutex;

    QString m_strFilePath;

    DataSourceType m_eType;//当前数据源类型
    QFile m_file;
    bool m_bSave;
};

#endif // DATAPARSER_H
