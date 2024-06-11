/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 用于产生测试数据
///
////////////////////////////////////////////

#ifndef SIMGEN_H
#define SIMGEN_H

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <QTimer>
#include <QVector>
#include <QMutex>

//TGAM模块 电源 信号质量 注意力 冥想值 eeg
const QList<uchar> TGAModules={0x01,0x02,0x04,0x05,0x83};

class SimGen : public QObject
{
    Q_OBJECT
public:
    explicit SimGen(QObject *parent = nullptr);
    ~SimGen();

    bool getBool();//return true/false
    int getNum(int max=256);//[0,max)

    QByteArray getOne(uchar mn, int max);//输入为modulename,max
    QByteArray getRaw();//
    QByteArray getEEG();

signals:
    void sendData(QByteArray ba);

private:
    QTimer *timer;
    int i=0;//计数
    QByteArray ms;//记录已经有的模块
};

#endif // SIMGEN_H
