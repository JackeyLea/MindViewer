/////////////////////
/// \author JackeyLea
/// \date 2024-10-29
/// \note 解析数据包并填充数据至结构体
/////////////////////

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QThread>

class DataParser : public QThread
{
    Q_OBJECT
public:
    DataParser();

    /// 获取一包数据并等待显示
    /// \brief getPkg
    /// \return
    ///
    QByteArray getPkg();

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
    void parsePkg();

    void run();

private:
    QByteArray m_buff;//数据缓存区
    QByteArrayList m_pkgList;//解析后的结构体列表
};

#endif // DATAPARSER_H
