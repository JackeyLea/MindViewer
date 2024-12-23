#include "simulator.h"

#include "icd.h"

Simulator::Simulator()
    :m_pTimer(new QTimer)
    ,m_unIterCnt(0)
{
    m_pTimer->setInterval(2);
    connect(m_pTimer,&QTimer::timeout,[=](){
        QByteArray strBuff;
        strBuff.clear();
        if(m_unIterCnt%512==0){//每512个包就有一个大包
            strBuff = getEEG();
        }else{//其他状态为小包
            strBuff = getRaw();
        }

        emit sigNewPkg(strBuff);

        if(m_unIterCnt > 3000000){
            m_unIterCnt=0;
        }
        ++m_unIterCnt;
    });
    m_pTimer->start();
}

Simulator::~Simulator()
{
    if(m_pTimer){
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}

QByteArray Simulator::getOne(uchar ucModelIndex, int iMax)
{
    QByteArray strModuleData;
    strModuleData.append((uchar)ucModelIndex);
    strModuleData.append(getNum(iMax));
    return strModuleData;
}

//16位raw value -32768~32767
//打包时分为两个uchar存储
QByteArray Simulator::getRaw(bool bNoise)
{
    QByteArray strPkt;
    strPkt.clear();

    strPkt.append(0xAA);
    strPkt.append(0xAA);
    strPkt.append(0x04);//包大小
    strPkt.append(0x80);//原始数据
    strPkt.append(0x02);//原始数据大小
    strPkt.append(getNum());//low
    strPkt.append(getNum());//high

    //计算校验值
    int iChecksum = strPkt[3];
    for (int k = 4; k < strPkt.size(); k++)
    {
        iChecksum += strPkt[k];
    }
    iChecksum &= 0xff;
    iChecksum = ~iChecksum & 0xff;
    strPkt.append(iChecksum);

    //添加随机干扰数据
    if(bNoise){
        int cnt = getNum();
        for(int n=0;n<cnt;n++){
            strPkt.append(getNum());
        }
        strPkt.append(0xaa);
    }

    return strPkt;
}

//大包不包含原始数据
//eeg数据有三个无符号整数组成
QByteArray Simulator::getEEG(bool bNoise)
{
    QByteArray strPkt;

    strPkt.clear();
    strPkt.append(0xAA);//0
    strPkt.append(0xAA);//1
    strPkt.append((char)0x00);// payload，先为空，等模块确定后才能确定

    //电源值
    strPkt.append(getOne(0x01,128));

    //信号强度
    strPkt.append(getOne(0x02,256));

    //心跳
    strPkt.append(getOne(0x03,256));

    //EEG
    //0x83后接18和24个EEG数据
    strPkt.append(0x83); //eeg
    strPkt.append(0x18); //eeg count value
    //delta
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //theta
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //lowalpha
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //highalpha
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //lowbeta
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //highbeta
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //lowgamma
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());
    //middlegamma
    strPkt.append(getNum());
    strPkt.append(getNum());
    strPkt.append(getNum());

    //注意力
    strPkt.append(getOne(0x04,100));
    //冥想值
    strPkt.append(getOne(0x05,100));

    //更新包长
    strPkt[2]=strPkt.size()-3;//末尾一个 两个0xaa

    //计算校验值
    int iChecksum = strPkt[3];
    for (int iDataIndex = 4; iDataIndex < strPkt.size(); iDataIndex++)
    {
        iChecksum += strPkt[iDataIndex];
    }
    iChecksum &= 0xff;
    iChecksum = ~iChecksum & 0xff;
    strPkt.append(iChecksum);

    //添加随机干扰数据
    if(bNoise){
        int iNoiseCnt = getNum();
        for(int iNoiseIndex=0;iNoiseIndex<iNoiseCnt;iNoiseIndex++){
            strPkt.append(getNum());
        }
    }

    return strPkt;
}
