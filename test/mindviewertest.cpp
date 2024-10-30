#include "mindviewertest.h"

#include "../MindViewer/simulator.h"
#include "../MindViewer/dataparser.h"

void MindViewerTest::case_checkGetRaw()
{
    Simulator sim;
    QByteArray ba = sim.getRaw();
    QVERIFY(ba.size()==8);
    QVERIFY((uchar)ba[0]==0xaa);
    QVERIFY((uchar)ba[1]==0xaa);
    QVERIFY(ba[2]==0x04);
    QVERIFY((uchar)ba[3]==0x80);
    QVERIFY(ba[4]==0x02);

    int checksum = 0;
    for(int i=3;i<ba.size()-1;i++){
        checksum += ba[i];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    QVERIFY(checksum==(uchar)ba[7]);
}

void MindViewerTest::case_checkGetEEG()
{
    Simulator sim;
    QByteArray ba = sim.getEEG();

    QVERIFY((uchar)ba[0]==0xaa);
    QVERIFY((uchar)ba[1]==0xaa);
    QVERIFY(ba[0]!=0x00);

    int checksum=0;
    for(int i=3;i<ba.size()-1;i++){
        checksum += ba[i];
    }
    checksum &= 0xff;
    checksum = ~checksum & 0xff;
    QVERIFY(checksum==(uchar)ba[ba.size()-1]);
}

void MindViewerTest::case_checkSkip()
{
    DataParser dp;
    QByteArray data;
    data.clear();
    data.append(0xAA);
    data.append(0xAA);
    data.append(0x04);//包大小
    data.append(0x80);//原始数据
    data.append(0x02);//原始数据大小
    data.append(0xFC);
    data.append(0xEE);
    data.append(0x93);
    dp.add2Buff(data);
    dp.skipInvalidByte();
    QByteArray res= dp.getBuff();
    QVERIFY((uchar)res[0]==0xaa);
    QVERIFY((uchar)res[1]==0xaa);
    QVERIFY((uchar)res[2]==0x04);
    QVERIFY((uchar)res[3]==0x80);
    QVERIFY((uchar)res[4]==0x02);
    QVERIFY((uchar)res[5]==0xfc);
    QVERIFY((uchar)res[6]==0xee);
    QVERIFY((uchar)res[7]==0x93);
    //data.append(0xFA);
    //data.append(0x79);//校验值0a
}

void MindViewerTest::case_checkSkip1()
{
    DataParser dp;
    QByteArray data;
    data.clear();
    data.append(0xab);
    data.append(0xbc);
    data.append(0xAA);
    data.append(0xAA);
    data.append(0x04);//包大小
    data.append(0x80);//原始数据
    data.append(0x02);//原始数据大小
    data.append(0xFC);
    data.append(0xEE);
    data.append(0x93);
    dp.add2Buff(data);
    dp.skipInvalidByte();
    QByteArray res= dp.getBuff();
    QVERIFY((uchar)res[0]==0xaa);
    QVERIFY((uchar)res[1]==0xaa);
    QVERIFY((uchar)res[2]==0x04);
    QVERIFY((uchar)res[3]==0x80);
    QVERIFY((uchar)res[4]==0x02);
    QVERIFY((uchar)res[5]==0xfc);
    QVERIFY((uchar)res[6]==0xee);
    QVERIFY((uchar)res[7]==0x93);
}

void MindViewerTest::case_checkSkip2()
{
    DataParser dp;
    QByteArray data;
    data.clear();
    data.append(0xAA);
    data.append(0xAA);
    data.append(0xAA);
    data.append(0x04);//包大小
    data.append(0x80);//原始数据
    data.append(0x02);//原始数据大小
    data.append(0xFC);
    data.append(0xEE);
    data.append(0x93);
    dp.add2Buff(data);
    dp.skipInvalidByte();
    QByteArray res= dp.getBuff();
    QVERIFY((uchar)res[0]==0xaa);
    QVERIFY((uchar)res[1]==0xaa);
    QVERIFY((uchar)res[2]==0x04);
    QVERIFY((uchar)res[3]==0x80);
    QVERIFY((uchar)res[4]==0x02);
    QVERIFY((uchar)res[5]==0xfc);
    QVERIFY((uchar)res[6]==0xee);
    QVERIFY((uchar)res[7]==0x93);
}
