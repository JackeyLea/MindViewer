/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 通用的数据结构
///
////////////////////////////////////////////

#ifndef ICD_H
#define ICD_H

#include <QObject>

//数据源类型
enum DataSourceType{
    None = 0,
    COM,
    Sim,
    Local
};

//eeg包可能包含的所有值
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
    uchar power;

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
        power=0;
    }
};//一个数据包包含的所有值

#endif // ICD_H
