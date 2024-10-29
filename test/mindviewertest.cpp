#include "mindviewertest.h"

#include "../MindViewer/simulator.h"

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
    QVERIFY(checksum==ba[7]);
}
