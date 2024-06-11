/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 通用的数据结构
///
////////////////////////////////////////////

#ifndef COMMON_H
#define COMMON_H

///////////////////////////以下内容来自官方参考代码//////////////////////////////////////
/* Parser types */
#define PARSER_TYPE_PACKETS    0x01    /* Stream bytes as ThinkGear Packets */
#define PARSER_TYPE_2BYTERAW   0x02    /* Stream bytes as 2-byte raw data */

/* Data CODE definitions */
#define PARSER_CODE_BATTERY            0x01
#define PARSER_CODE_POOR_QUALITY       0x02
#define PARSER_CODE_ATTENTION          0x04
#define PARSER_CODE_MEDITATION         0x05
#define PARSER_CODE_8BITRAW_SIGNAL     0x06
#define PARSER_CODE_RAW_MARKER         0x07

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

#define PARSER_CODE_RAW_SIGNAL         0x80
#define PARSER_CODE_EEG_POWERS         0x81
#define PARSER_CODE_ASIC_EEG_POWER_INT 0x83
/////////////////////////////////////////////////////////////////////////////////////////////////////

#define uchar unsigned char

//eeg包可能包含的所有值
struct _eegPkt{
    bool isRawValid;
    short raw;
    bool isEEGValid;
    int delta;
    int theta;
    int lowAlpha;
    int highAlpha;
    int lowBeta;
    int highBeta;
    int lowGamma;
    int midGamma;
    bool isAttentionValid;
    uchar attention;//0-100
    bool isMeditationValid;
    uchar meditation;//0-100
    int blink;//1-255
    uchar mwl;//mind-wandering level 走神程度 0-10
    bool isSignalValid;
    uchar signal;//0-200
    bool isPowerValid;
    uchar power;//电源指示0-100

    void init(){
        isRawValid=false;
        raw=0;
        isEEGValid=false;
        delta=0;
        theta=0;
        lowAlpha=0;
        highAlpha=0;
        lowBeta=0;
        highBeta=0;
        lowGamma=0;
        midGamma=0;
        isAttentionValid=false;
        attention=0;
        isMeditationValid=false;
        meditation=0;
        blink=0;
        mwl=0;
        isSignalValid=false;
        signal=0;
        isPowerValid=false;
        power=0;
    }
};//一个数据包包含的所有值

#endif // COMMON_H
