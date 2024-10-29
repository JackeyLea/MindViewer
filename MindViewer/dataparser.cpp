#include "dataparser.h"

#include <QDebug>

DataParser::DataParser()
{
    //初始化数据
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::clearBuff()
{
    m_buff.clear();
}

void DataParser::run()
{
    while(1){
        if(m_buff.size()>0){

        }else{
            qDebug()<<"DataParser::run() -> sleep 30ms";
            QThread::msleep(30);
        }
    }
}
