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

protected:

    /// 校验当前是否为有效数据包
    /// \brief checkPkg
    ///
    void checkPkg();

    /// 解析一个有效数据包，但是数据不一定有效
    /// \brief parsePkg
    ///
    int parsePkg(QByteArray ba, bool &raw, short &rawValue, bool &common, bool &eeg, _eegPkt &pkt);

    void run();

private:
    void sltRcvData(QByteArray ba);

private:
    QByteArray m_buff;//数据缓存区
    QList<_eegPkt> m_pkgList;//解析后的结构体列表

    Retriver *m_comRetriver;

    QByteArray mBuff;
};

#endif // DATAPARSER_H
