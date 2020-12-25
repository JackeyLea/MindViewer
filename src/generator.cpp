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
            QByteArray data;
            data.append(0xAA); //0
            data.append(0xAA); //1
            data.append(0x04);    //payload
            data.append(0x80);
            data.append(0x02);
            data.append(getNum());
            data.append(getNum());
            int size=data.size();
            int checksum=data[size-1]+data[size-2];
            checksum &= 0xff;
            checksum = ~checksum & 0xff;
            data.append(checksum);
            emit sendData(data);
        }
        //qDebug()<<eegPkg();
        QByteArray data;
        data.append(0xAA); //0
        data.append(0xAA); //1
        data.append(0x20);    //payload
        //signal
        data.append(0x02);        //signal
        data.append(getNum(256)); //signal value
    //    //power
    //    data.append(0x01);
    //    data.append(getNum(128)); //3v
        //eeg power
        data.append(0x83); //eeg power
        data.append(0x18);    //eeg power value
        //delta
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //theta
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //lowalpha
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //highalpha
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //lowbeta
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //highbeta
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //lowgamma
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //middlegamma
        data.append(getNum(256));
        data.append(getNum(256));
        data.append(getNum(256));
        //attention
        data.append(0x04);
        data.append(getNum(101));
        //meditation
        data.append(0x05);
        data.append(getNum(101));

        //calculate sumcheck
        int checksum = data[3];
        for (int i = 4; i <= data.size() - 1; i++)
        {
            checksum += data[i];
        }
        checksum &= 0xff;
        checksum = ~checksum & 0xff;
        data.append(checksum);
        emit sendData(data);
        mutex.unlock();
    });
    timer->start();
    if(isStop){
        timer->stop();
        delete timer;
    }
    this->exec();
}
