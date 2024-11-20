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
#include <QRandomGenerator>

/* Parser types */
#define PARSER_TYPE_NULL       0x00
#define PARSER_TYPE_PACKETS    0x01    /* Stream bytes as ThinkGear Packets */
#define PARSER_TYPE_2BYTERAW   0x02    /* Stream bytes as 2-byte raw data */

/* Data CODE definitions */
#define PARSER_CODE_BATTERY            0x01
#define PARSER_CODE_POOR_QUALITY       0x02
#define PARSER_CODE_ATTENTION          0x04
#define PARSER_CODE_MEDITATION         0x05
#define PARSER_CODE_8BITRAW_SIGNAL     0x06
#define PARSER_CODE_RAW_MARKER         0x07

#define PARSER_CODE_RAW_SIGNAL         0x80
#define PARSER_CODE_EEG_POWERS         0x81
#define PARSER_CODE_ASIC_EEG_POWER_INT 0x83

/* Decoder states (Packet decoding) */
#define PARSER_STATE_NULL           0x00  /* NULL state */
#define PARSER_STATE_SYNC           0x01  /* Waiting for SYNC byte */
#define PARSER_STATE_SYNC_CHECK     0x02  /* Waiting for second SYNC byte */
#define PARSER_STATE_PAYLOAD_LENGTH 0x03  /* Waiting for payload[] length */
#define PARSER_STATE_CHKSUM         0x04  /* Waiting for chksum byte */
#define PARSER_STATE_PAYLOAD        0x05  /* Waiting for next payload[] byte */

/* Decoder states (2-byte raw decoding) */
#define PARSER_STATE_WAIT_HIGH      0x06  /* Waiting for high byte */
#define PARSER_STATE_WAIT_LOW       0x07  /* High r'cvd.  Expecting low part */

/* Other constants */
#define PARSER_SYNC_BYTE            0xAA  /* Syncronization byte */
#define PARSER_EXCODE_BYTE          0x55  /* EXtended CODE level byte */

//[0,max)
inline uchar getNum(int max=256){
    return QRandomGenerator::global()->bounded(0,max);
}

inline uchar hex2int(char x) {
    return ( (x>='0' && x<='9') ? (x-'0') : ((x>='a' && x<='f') ? (x-'a' +10) : (x-'A' + 10)));
}

inline uchar hex2ba(QString x) {
    assert(x.size()==2);
    return (hex2int(x.at(0).toLatin1()) * 16 + hex2int(x.at(1).toLatin1()));
}

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
    int noise;//噪声数量
    int total;//总包数
    int loss;//丢失数
    int rawCnt;//原始包数
    QVector<double> raw;

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
        noise =0;
        total=0;
        loss=0;
        rawCnt=0;
        raw.clear();
    }
};//一个数据包包含的所有值

#endif // ICD_H
