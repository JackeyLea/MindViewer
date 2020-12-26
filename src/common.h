#ifndef COMMON_H
#define COMMON_H

#include <QCoreApplication>

struct _eegPkt{
    int delta;
    int theta;
    int lowAlpha;
    int highAlpha;
    int lowBeta;
    int highBeta;
    int lowGamma;
    int midGamma;
    uchar attention;//0-100
    uchar meditation;//0-100
    int blink;//1-255
    uchar mwl;//mind-wandering level 走神程度 0-10
    uchar signal;//0-200

    void init(){
        delta=0;
        theta=0;
        lowAlpha=0;
        highAlpha=0;
        lowBeta=0;
        highBeta=0;
        lowGamma=0;
        midGamma=0;
        attention=0;
        meditation=0;
        blink=0;
        mwl=0;
        signal=0;
    }
};//一个数据包包含的所有值

//16位raw value -32768~32767
//eeg数据有三个无符号整数组成

//下为一个典型数据包的数据顺序和类型和类别
typedef struct type1
{
    int ASYN1;
    int ASYN2;
    int PAYLOAD;
    int Signal;
    int SignalValue;
    int Power;
    int PowerValue;
    int Delta1;
    int Delta2;
    int Delta3;
    int Theta1;
    int Theta2;
    int Theta3;
    int LowAlpha1;
    int LowAlpha2;
    int LowAlpha3;
    int HighAlpha1;
    int HightAlpha2;
    int HightAlpha3;
    int LowBeta1;
    int LowBeta2;
    int LowBeta3;
    int HighBeta1;
    int HighBeta2;
    int HighBeta3;
    int LowGamma1;
    int LowGamma2;
    int LowGamma3;
    int MiddleGamma1;
    int MiddleGamma2;
    int MiddleGamma3;
    int Attention;
    int AttentionValue;
    int Meditation;
    int MeditationValue;
    int checksum;
} type1;

#endif // COMMON_H
