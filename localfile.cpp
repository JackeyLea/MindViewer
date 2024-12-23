#include "localfile.h"
#include "icd.h"

#include <QFile>
#include <QDebug>

LocalFile::LocalFile(const QString& strFilePath, QObject *parent)
    : QObject{parent}
    ,m_strFilePath(strFilePath)
{}

void LocalFile::fileParse()
{
    QFile file(m_strFilePath);

    if(!file.open(QFile::ReadOnly)){
        qDebug()<<"Cannot open file.";
        return;
    }
    while(!file.atEnd()){
        QString strLineData = file.readLine();
        strLineData.remove('\r');
        strLineData.remove('\n');

        QByteArray strBuff;
        QStringList dataList = strLineData.split(' ');
        for(int i=0;i<dataList.size();i++){
            if(dataList[i].isEmpty()) continue;
            strBuff.append(hex2ba(dataList[i]));
        }
        emit sigNewPkg(strBuff);
    }

    file.close();
}
