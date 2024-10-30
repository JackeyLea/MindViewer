#include "simulator.h"

#include "icd.h"

Simulator::Simulator()
{
    isStop=false;
    //buff.resize(1024 * 1024);

    timer = new QTimer();
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,[=](){
        QByteArray buff;
        buff.clear();
        if(i%51==0){//每512个包就有一个大包
            buff = getEEG();
        }else{//其他状态为小包
            buff = getRaw();
        }

        emit sigNewPkg(buff);

        if(i > 3000000){
            i=0;
        }
        ++i;
    });
    timer->start();
}

Simulator::~Simulator()
{
    timer->stop();
    delete timer;
}

QByteArray Simulator::getOne(uchar mn, int max)
{
    QByteArray data;
    data.append((uchar)mn);
    data.append(getNum(max));
    return data;
}
//16位raw value -32768~32767
//打包时分为两个uchar存储
QByteArray Simulator::getRaw(bool noise)
{
    QByteArray data;
    data.clear();
    data.append(0xAA);
    data.append(0xAA);
    data.append(0x04);//包大小
    data.append(0x80);//原始数据
    data.append(0x02);//原始数据大小
    data.append(getNum());//low
    data.append(getNum());//high
    //计算校验值
    int checksum = data[3];
    for (int i = 4; i < data.size(); i++)
    {
        checksum += data[i];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    data.append(checksum);
    //qDebug()<<"raw data"<<data;

    //添加随机干扰数据
    if(noise){
        int cnt = getNum();
        for(int n=0;n<cnt;n++){
            data.append(getNum());
        }
        data.append(0xaa);
    }

    return data;
}

//大包不包含原始数据
//eeg数据有三个无符号整数组成
QByteArray Simulator::getEEG(bool noise)
{
    QByteArray pkg;

    pkg.clear();
    pkg.append(0xAA);//0
    pkg.append(0xAA);//1
    pkg.append((char)0x00);// payload，先为空，等模块确定后才能确定

    //电源值
    pkg.append(getOne(0x01,128));

    //信号强度
    pkg.append(getOne(0x02,256));
    //心跳
    pkg.append(getOne(0x03,256));

    //EEG
    //0x83后接18和24个EEG数据
    pkg.append(0x83); //eeg
    pkg.append(0x18); //eeg count value
    //delta
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //theta
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //lowalpha
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //highalpha
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //lowbeta
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //highbeta
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //lowgamma
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());
    //middlegamma
    pkg.append(getNum());
    pkg.append(getNum());
    pkg.append(getNum());

    //注意力
    pkg.append(getOne(0x04,100));
    //冥想值
    pkg.append(getOne(0x05,100));

    //update plength
    //qDebug()<<"size "<<pkg.size();
    pkg[2]=pkg.size()-3;//末尾一个 两个0xaa
    //calculate sumcheck
    int checksum = pkg[3];
    for (int i = 4; i < pkg.size(); i++)
    {
        checksum += pkg[i];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    pkg.append(checksum);

    //添加随机干扰数据
    if(noise){
        int cnt = getNum();
        for(int n=0;n<cnt;n++){
            pkg.append(getNum());
        }
    }

    return pkg;
}
