///////////////////
/// \author JackeyLea
/// \date 2024-10-31
/// \note 本地文件解析类
///////////////////

#ifndef LOCALFILE_H
#define LOCALFILE_H

#include <QObject>

class LocalFile : public QObject
{
    Q_OBJECT
public:
    explicit LocalFile(const QString filePath, QObject *parent = nullptr);

    void fileParse();

signals:
    /// 通知界面已经成功解析一包
    /// \brief sigNewPkg
    /// \param ba
    ///
    void sigNewPkg(QByteArray ba);

private:
    QString m_filePath;
};

#endif // LOCALFILE_H
