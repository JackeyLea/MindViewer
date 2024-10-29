#include "dataparser.h"

#include <QDebug>

DataParser::DataParser()
{
    //初始化数据
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::setSource(DataSourceType type)
{
    switch(type){
    case None:
        break;
    case COM:
        m_comRetriver = new Retriver(NULL);
        m_comRetriver->showWgt();
        break;
    case Sim:
        break;
    case Local:
        break;
    }
}

_eegPkt DataParser::getPkg()
{
    if(m_pkgList.size()==0){
        return _eegPkt();
    }
    return m_pkgList.takeFirst();
}

void DataParser::clearBuff()
{
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::run()
{
    while(1){
        if(m_buff.size()>0){

        }else{
            qDebug()<<"DataParser::run() -> sleep 30ms";
            _eegPkt pkt;
            pkt.init();
            pkt.power = 12;
            m_pkgList.append(pkt);
            QThread::msleep(30);
        }
    }
}
