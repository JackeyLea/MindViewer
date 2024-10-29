#include "dataparser.h"

#include <QDebug>

DataParser::DataParser()
{
    //初始化数据
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::setSource(DataSourceType type)
{
    switch(type){
    case None:
        break;
    case COM:
        m_comRetriver = new Retriver(NULL);
        m_comRetriver->showWgt();
        break;
    case Sim:
        break;
    case Local:
        break;
    }
}

_eegPkt DataParser::getPkg()
{
    if(m_pkgList.size()==0){
        return _eegPkt();
    }
    return m_pkgList.takeFirst();
}

void DataParser::clearBuff()
{
    m_buff.clear();
    m_pkgList.clear();
}

void DataParser::skipInvalidByte()
{
    if(mBuff.size()==0) return;

    //一个包最起码包含一个有效数据类型0xaa 0xaa 0x02 0xaa 0xaa
    // 此时包肯定不完整，就结束
    if(mBuff.size()<=5) return;

    //有可能一次收的数据不完整先判断
    while(mBuff.size()){
        //可能会出现这种情况 0xaa 0xaa 0xaa
        if(mBuff[0]==0xaa && mBuff[1]==0xaa && mBuff[2]==0xaa){
            mBuff.removeFirst();
            continue;
        }
        if(mBuff[0]==0xAA && mBuff[1]==0xAA){//先找包头
            //包大小
            int pkgSize = mBuff[2];
            //最后的checksum + 本身 + 2个同步
            if(pkgSize + 2 + 1+ 1 > mBuff.size()){
                qDebug()<<"pkg is less than given size.";
                mBuff.removeFirst();
                continue;
            }
        }else{
            //如果前两个不是0xAA 0xAA就向后移一位
            mBuff.removeFirst();
            qDebug()<<"remove "<<mBuff;
        }
    }
}

//使用状态机解析原始数据
int DataParser::parsePkg(QByteArray ba, bool &raw, short &rawValue, bool &common, bool &eeg, struct _eegPkt &pkt)
{
    //输入的数据ba只包含一个有效包
    //qDebug()<<"parse start";
    raw=false;//此数据包是否包含原始数据
    eeg=false;//此数据包是否包含eeg数据
    common=false;//此数据包是否包含注意力/冥想等数据

    if(ba.isEmpty()) return -1;//如果没有数据就直接退出

    //qDebug()<<"add to buff."<<ba.size();
    QByteArray buff = ba;//将数据添加到处理缓冲区

    /////////////////处理开始/////////////////////////////////////
    int cnt=0;
    uchar state=PARSER_STATE_SYNC;
    uchar payloadLength=0;
    uchar payloadSum=0;
    while(buff.size()){
        //qDebug()<<buff;
        //状态机处理
        switch(state){
        case PARSER_STATE_SYNC://第一个同步字节
            if((uchar)buff[0]==PARSER_SYNC_BYTE){
                //qDebug()<<"parser first aa "<<i<<(uchar)buff[i];
                state=PARSER_STATE_SYNC_CHECK;
            }
            buff.remove(0,1);
            break;
        case PARSER_STATE_SYNC_CHECK:
            if((uchar)buff[0]==PARSER_SYNC_BYTE){//包第二个0xaa
                //qDebug()<<"parser second aa "<<i<<(uchar)buff[i];
                state=PARSER_STATE_PAYLOAD_LENGTH;//准备解析负载长度
                buff.remove(0,1);
            }
            break;
        case PARSER_STATE_PAYLOAD_LENGTH:
            payloadLength=(uchar)buff[0];//接下来是长度
            //qDebug()<<"payloadlength"<<payloadLength;
            if(payloadLength>=170 || payloadLength<=0){//如果长度大于170就丢弃此包并查找下一个0xaa 0xaa
                qDebug()<<"this package payloadLength(the 3rd value) is wrong";
                state = PARSER_STATE_SYNC;
                //如果是0xaa 0xaa 0xff，包头对了但是长度不对
            }else{
                //qDebug()<<"parser payload length "<<i<<(uchar)buff[i];
                state=PARSER_STATE_CHKSUM;//准备解析有效数据
            }
            buff.remove(0,1);
            break;
        case PARSER_STATE_CHKSUM:
        {
            //qDebug()<<"check sum"<<payloadLength+1<<buff.size();
            //如果剩余大小不够 1是末尾的校验值 3是包头和大小
            if(payloadLength+1 >buff.size()){
                qDebug()<<"pkg is not valid.";
                state = PARSER_STATE_SYNC;
                break;
            }
            //执行到这里表示此时包是完整的，后续解析其实不需要判断包大小
            //首先校验数据是否有效
            payloadSum=0;
            for(int j=0;j<payloadLength;j++){
                //qDebug()<<(uchar)buff[j];
                payloadSum+=(uchar)buff[j];
            }
            payloadSum &= 0xff;
            payloadSum = ~payloadSum & 0xff;

            //qDebug()<<"add"<<payloadSum<<(uchar)buff[payloadLength];
            if(payloadSum!=(uchar)buff[payloadLength]){
                //如果与校验值不同就丢弃此包数据
                qDebug()<<"Checksum failed.";
                return -1;
            }
            //qDebug()<<"get data check sum is: "<<z<<(uchar)buff[z];
            //qDebug()<<"parser check sum "<<i;
            state=PARSER_STATE_PAYLOAD;
            //到此可以正常解析数据了
            break;
        }
        case PARSER_STATE_PAYLOAD://解析数据
        {
            //qDebug()<<"payload"<<buff;
            if(cnt==payloadLength){
                buff.remove(0,1);//如果数据已经没了，那么还剩下一个校验值
                break;
            }
            if((uchar)buff[0]==0x01){//电源值，最大为127
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    common = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                common=true;
                pkt.power=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x02){//数据信号强度值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    common= false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                //qDebug()<<"signal value "<<(uchar)buff[1];
                common=true;
                pkt.signal=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x03){
                //ego上的心跳强度0-255
            }else if((uchar)buff[0]==0x04){//注意力值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    common = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                //qDebug()<<"attention value "<<(uchar)buff[1];
                common=true;
                pkt.attention=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x05){//冥想值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    common = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                //qDebug()<<"meditation value "<<(uchar)buff[1];
                common=true;
                pkt.meditation=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x06){//8bit raw value
            }else if((uchar)buff[0]==0x07){
                //raw_marker 固定值为0
            }else if((uchar)buff[0]==0x80 && (uchar)buff[1]==0x02){//16位原始数据
                //qDebug()<<"raw data";
                //如果缓冲区大小小于5位
                if(buff.size() < 5){
                    raw = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                raw=true;
                rawValue=((uchar)buff[2]<<8)|(uchar)buff[3];
                buff.remove(0,5);//4个数据以及最后的校验值
                break;
            }else if((uchar)buff[0]==0x81 && (uchar)buff[1]==0x20){
                //eeg_power 8个大端四字节
            }else if((uchar)buff[0]==0x83 && (uchar)buff[1]==0x18){//eeg数据部分
                //0x83标志eeg部分开始，下一位表示为eeg部分程度默认为0x18,8个大端三字节
                //qDebug()<<"parser eeg data "<<i<<buff[i];
                //qDebug()<<"parser eeg length "<<(uchar)buff[i+1];
                //如果缓冲区大小小于24位
                if(buff.size() < 26){
                    eeg = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                eeg=true;
                //tgam数据默认为大端
                pkt.delta =((uint)buff[2]<<16)|((uint)buff[3]<<8)|((uint)buff[4]);
                pkt.theta =((uint)buff[5]<<16)|((uint)buff[6]<<8)|((uint)buff[7]);
                pkt.lowAlpha =((uint)buff[8]<<16)|((uint)buff[9]<<8)|((uint)buff[10]);
                pkt.highAlpha =((uint)buff[11]<<16)|((uint)buff[12]<<8)|((uint)buff[13]);
                pkt.lowBeta =((uint)buff[14]<<16)|((uint)buff[15]<<8)|((uint)buff[16]);
                pkt.highBeta =((uint)buff[17]<<16)|((uint)buff[18]<<8)|((uint)buff[19]);
                pkt.lowGamma =((uint)buff[20]<<16)|((uint)buff[21]<<8)|((uint)buff[22]);
                pkt.midGamma =((uint)buff[23]<<16)|((uint)buff[24]<<8)|((uint)buff[25]);
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,26);//24 + 2
                cnt+=26;
            }else if((uchar)buff[0]==0x86 && (uchar)buff[1]==0x02){
                //两个大端字节表示R峰的间隔
            }
            break;
        }
        case PARSER_STATE_NULL:
            break;
        default:
            break;
        }
    }

    //qDebug()<<"parse end.";

    return 0;
}

void DataParser::run()
{
    while(1){
        if(m_buff.size()>0){
            //这里用while是考虑缓冲区可能有不止一个包
            while(mBuff.size()>=5){
                assert(mBuff[0]!=(uchar)0xaa);
                assert(mBuff[1]!=(uchar)0xaa);

                //第3个字节是长度
                int length = mBuff[2];
                QByteArray tmpBA = mBuff.mid(0,length+2+1+1);
                qDebug()<<"one pkg"<<tmpBA;
                //从缓冲区删除已经解析的包
                qDebug()<<"before delete"<<mBuff;
                mBuff.remove(0,length+4);
                qDebug()<<"after delete"<<mBuff;
                //解析函数一次只解析一个包
                bool raw,eeg,common;
                short rawValue;
                struct _eegPkt pkt;
                pkt.init();
                if(parsePkg(tmpBA,raw,rawValue,common,eeg,pkt)!=0){
                    qDebug()<<"Cannot parse data.";
                    //错误数据已经从缓存区删除，直接进行下一次解析
                }
                qDebug()<<"parsered";
            }//while
            qDebug()<<"mBuff"<<mBuff;
        }else{//if
            qDebug()<<"DataParser::run() -> sleep 30ms";
            _eegPkt pkt;
            pkt.init();
            pkt.power = 12;
            m_pkgList.append(pkt);
            QThread::msleep(30);
        }
    }
}

void DataParser::sltRcvData(QByteArray ba)
{
    //收到数据后填充至缓存区等待解析
    m_buff.append(ba);
}
