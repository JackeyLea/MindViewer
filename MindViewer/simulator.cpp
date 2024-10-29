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

        emit sigNewPkt(buff);

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
    //    QByteArray pkg;
    //    pkg.clear();
    //    if(isFront){
    //        pkg.append(0xAA);
    //        pkg.append(0xAA);
    //        pkg.append(0x04);//包大小
    //    }else{
    ////        pkg.append(0x80);//原始数据
    ////        pkg.append(0x02);//原始数据大小
    ////        pkg.append(0xFC);
    ////        pkg.append(0xEE);//经验值93
    ////        pkg.append(0x93);
    //        pkg.append(0x80);//原始数据
    //        pkg.append(0x02);//原始数据大小
    //        pkg.append(getNum());//low
    //        pkg.append(getNum());//high
    //        //计算校验值
    //        int checksum = pkg[0];
    //        for (int i = 1; i < pkg.size(); i++)
    //        {
    //            checksum += pkg[i];
    //        }
    //        checksum &= 0xff;
    //        checksum = ~checksum & 0xff;
    //        pkg.append(checksum);
    //    }
    //    isFront = !isFront;
    //    return pkg;
    QByteArray data;
    data.clear();
    data.append(0xAA);
    data.append(0xAA);
    data.append(0x04);//包大小
    data.append(0x80);//原始数据
    data.append(0x02);//原始数据大小
    data.append(getNum());//low
    data.append(getNum());//high
    //用于验证包是否正确
    //data.append(0xFC);
    //data.append(0xEE);//经验值93
    //data.append(0xFA);
    //data.append(0x79);//校验值0a
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
//大包
//各个模块对应的部分不一定出现，出现的顺序也不一定
//处理流程为
//随机选择一个模块，判断这个模块是否已经有了
//如果还没有这个模块，获取随机数决定是否添加
//大包不包含原始数据
//eeg数据有三个无符号整数组成
QByteArray Simulator::getEEG()
{
    //    QByteArray pkg2;
    //    pkg2.clear();
    //    if(eegfront){
    //        pkg2.append(0xaa);
    //        pkg2.append(0xaa);
    //    }else{
    //        pkg2.append(0x08);
    //        pkg2.append(0x02);
    //        pkg2.append(0x20);
    //        pkg2.append(0x01);
    //        pkg2.append(0x7e);
    //        pkg2.append(0x04);
    //        pkg2.append(0x12);
    //        pkg2.append(0x05);
    //        pkg2.append(0x60);
    //        pkg2.append(0xe3);
    //    }
    //    eegfront = !eegfront;
    //    return pkg2;
    QByteArray pkg;

    while(true){
        ms.clear();

        pkg.clear();
        pkg.append(0xAA);//0
        pkg.append(0xAA);//1
        pkg.append((int)0x00);// payload，先为空，等模块确定后才能确定

        //使用两个循环，外层决定是否使用，内层决定使用哪一个模块
        for(int i=0;i<5;i++){//是否使用
            bool isUse = getBool();
            if(!isUse){//不使用当前模块
                continue;
            }
            //如果使用当前模块
            for(int j=0;j<5;j++){
                int module = getNum(5);
                //qDebug()<<module;
                if(!ms.contains(module)){
                    ms.append(module);
                    switch(TGAModules[module]){
                    case 0x83://EEG
                    {
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
                        break;
                    }
                    case 0x01://电源值
                        pkg.append(getOne(0x01,128));
                        break;
                    case 0x02://信号强度
                        pkg.append(getOne(0x02,256));
                        break;
                    case 0x04://注意力
                        pkg.append(getOne(0x04,100));
                        break;
                    case 0x05://冥想值
                        pkg.append(getOne(0x05,100));
                        break;
                    }
                }
            }
        }
        //update plength
        //qDebug()<<"size "<<pkg.size();
        pkg[2]=pkg.size()-3;
        //qDebug()<<"2"<<(int)pkg[2];
        if((int)pkg[2]==0){//如果所有模块都未被使用，就重新生成
            continue;
        }
        //qDebug()<<ms;
        if(!ms.contains(4)){//必须有eeg数据，如果没有就重新生成
            continue;
        }
        //calculate sumcheck
        int checksum = pkg[3];
        for (int i = 4; i < pkg.size(); i++)
        {
            checksum += pkg[i];
        }
        checksum &= 0xff;
        checksum = ~checksum & 0xff;
        pkg.append(checksum);
        //qDebug()<<"eeg"<<pkg;
        break;
    }

    //添加随机干扰数据
    int cnt = getNum();
    for(int n=0;n<cnt;n++){
        pkg.append(getNum());
    }
    pkg.append(0xaa);

    return pkg;
}
