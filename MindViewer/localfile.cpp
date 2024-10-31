#include "localfile.h"
#include "icd.h"

#include <QFile>
#include <QDebug>

LocalFile::LocalFile(QString filePath, QObject *parent)
    : QObject{parent}
{
    m_filePath = filePath;
}

void LocalFile::fileParse()
{
    QFile file(m_filePath);

    if(!file.open(QFile::ReadOnly)){
        qDebug()<<"Cannot open file.";
        return;
    }
    while(!file.atEnd()){
        QString line = file.readLine();
        line.remove('\r');
        line.remove('\n');

        QByteArray ba;
        QStringList dataList = line.split(' ');
        for(int i=0;i<dataList.size();i++){
            if(dataList[i].isEmpty()) continue;
            ba.append(hex2ba(dataList[i]));
        }
        qDebug()<<ba;
        emit sigNewPkg(ba);
    }

    file.close();
}
