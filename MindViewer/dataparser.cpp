#include "dataparser.h"

DataParser::DataParser()
{
    //初始化数据
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::run()
{
    while(1){
        if(m_buff.size()>0){

        }else{
            QThread::msleep(30);
        }
    }
}
