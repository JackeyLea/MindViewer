#include "generator.h"

Generator::Generator()
{
    isStop=false;
}

Generator::~Generator()
{
}

int Generator::getNum(int max)
{
    return QRandomGenerator::global()->bounded(max);
}
//(-,+)
int Generator::getNum()
{
    return QRandomGenerator::global()->bounded(0,256);
}

QByteArray Generator::getRaw()
{
    //qDebug()<<"Generating raw data";
    QByteArray data;
    data.append(0xAA); //0
    data.append(0xAA); //1
    data.append(0x04); //payload
    data.append(0x80);
    data.append(0x02);
    uchar a=getNum();
    data.append(a);
    uchar b=getNum();
    data.append(b);
    //short rawValue=((uchar)b<<8)|(uchar)a;
    //qDebug()<<"generated a is: "<<a;
    //qDebug()<<"generated b is: "<<b;
    //qDebug()<<"generated rawvalue is: "<<rawValue;
    int size=data.size();
    int checksum=0;
    for(int j=3;j<size;j++){
        checksum+=data[j];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    data.append(checksum);

//    QVector<uchar> c;
//    for(int i=0;i<data.size();i++){
//        c.append((uchar)data[i]);
//    }
    //qDebug()<<"data is: "<<c;
    //qDebug()<<"raw data generated";

    return data;
}

QByteArray Generator::getEEG()
{
    //qDebug()<<"generating eeg data";
    QByteArray data;
    data.append(0xAA); //0
    data.append(0xAA); //1
    data.append(0x20); //payload
    //signal
    data.append(0x02); //signal
    data.append(getNum()); //signal value
    //    //power
    //    data.append(0x01);
    //    data.append(getNum(128)); //3v
    //eeg power
    data.append(0x83); //eeg power
    data.append(0x18); //eeg power value
    //delta
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //theta
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //lowalpha
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //highalpha
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //lowbeta
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //highbeta
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //lowgamma
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //middlegamma
    data.append(getNum());
    data.append(getNum());
    data.append(getNum());
    //attention
    data.append(0x04);
    int t=getNum(101);
    data.append(t);
    //meditation
    data.append(0x05);
    data.append(getNum(101));

    //calculate sumcheck
    int checksum = data[3];
    for (int i = 4; i < data.size(); i++)
    {
        checksum += data[i];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    data.append(checksum);

//    QVector<uint> a;
//    for(int i=0;i<data.size();i++){
//        a.append((uint)data[i]);
//    }
//    qDebug()<<a;

    //qDebug()<<"eeg data generated";
    return data;
}

void Generator::stopNow()
{
    isStop=true;
    this->quit();
    this->wait();
}

void Generator::run()
{
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,[=](){
        mutex.lock();
        //输出time s的模拟数据
        for (int i = 0; i < 511; i++)
        {//每秒钟约512个包
            QByteArray ba = getRaw();
            emit sendData(ba);
        }
        QByteArray ba=getEEG();
        emit sendData(ba);
        mutex.unlock();
    });
    timer->start();
    if(isStop){
        timer->stop();
        delete timer;
    }
    this->exec();
}
