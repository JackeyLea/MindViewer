#include "dataparser.h"

#include <QDebug>

DataParser::DataParser()
    :m_comRetriver(nullptr)
    ,m_sim(nullptr)
    ,m_lf(nullptr)
    ,m_noise(0)
    ,m_total(0)
    ,m_loss(0)
    ,m_rawCnt(0)
    ,m_eType(None)
    ,m_bSave(false)
{
    //初始化数据
    m_buff.clear();
    m_pkgList.clear();
    m_rawData.clear();
    m_filePath.clear();
}

DataParser::~DataParser()
{
    if(!m_bSave){
        if(file.isOpen()){
            file.remove();
        }
    }
    file.close();

    if(m_comRetriver){
        m_comRetriver->stopCOM();
        m_comRetriver->deleteLater();
        m_comRetriver = nullptr;
    }
    if(m_sim){
        m_sim->deleteLater();
        m_sim = nullptr;
    }
}

void DataParser::saveLocalFile()
{
    file.close();
    m_bSave = true;
}

void DataParser::setFilePath(const QString path)
{
    m_filePath = path;
}

void DataParser::setSource(DataSourceType type)
{
    m_eType = type;
    switch(type){
    case None:
        break;
    case COM:
    {
        if(!m_comRetriver){
            m_comRetriver = new Retriver(NULL);
        }
        m_comRetriver->showWgt();
        connect(m_comRetriver,&Retriver::sigNewPkg,this,&DataParser::sltRcvData);
        //清理之前状态
        if(m_sim){
            m_sim->disconnect();
        }
        if(m_lf){
            m_lf->disconnect();
        }
        //本地文件
        QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".txt";
        file.setFileName(fileName);
        if(!file.open(QFile::WriteOnly)){
            qDebug()<<"Cannot open local file.";
        }
        break;
    }
    case Sim:
    {
        if(!m_sim){
            m_sim = new Simulator();
        }
        connect(m_sim,&Simulator::sigNewPkg,this,&DataParser::sltRcvData);
        //清理之前状态
        if(m_lf){
            m_lf->disconnect();
        }
        if(m_comRetriver){
            m_comRetriver->disconnect();
        }
        break;
    }
    case Local:
    {
        if(!m_lf){
            m_lf = new LocalFile(m_filePath);
        }
        connect(m_lf,&LocalFile::sigNewPkg,this,&DataParser::sltRcvData);
        m_lf->fileParse();
        //清理之前状态
        if(m_sim){
            m_sim->disconnect();
        }
        if(m_comRetriver){
            m_comRetriver->disconnect();
        }
        break;
    }
    }
}

void DataParser::clearBuff()
{
    m_mutex.lock();
    m_buff.clear();
    m_mutex.unlock();

    m_pkgList.clear();
    m_rawData.clear();
    m_noise=0;
    m_total=0;
    m_loss=0;
    m_rawCnt=0;
}

void DataParser::skipInvalidByte()
{
    if(m_buff.size()==0) return;

    //一个包最起码包含一个有效数据类型0xaa 0xaa 0x02 0x02 0x01 0xaa
    // 此时包肯定不完整，就结束
    if(m_buff.size()<=6) {
        m_buff.clear();
        return;
    }

    //有可能一次收的数据不完整先判断
    while(m_buff.size()>=6){
        //可能会出现这种情况 0xaa 0xaa 0xaa
        if((uchar)m_buff[0]==0xaa && (uchar)m_buff[1]==0xaa && (uchar)m_buff[2]==0xaa){
            qDebug()<<"3 0xaa found.";
            m_noise++;
            m_mutex.lock();
            m_buff.removeFirst();
            m_mutex.unlock();
            continue;
        }else if((uchar)m_buff[0]==0xAA && (uchar)m_buff[1]==0xAA){//先找包头
            //包大小
            int pkgSize = (uchar)m_buff[2];
            //最后的checksum + 本身 + 2个同步
            if(pkgSize + 2 + 1+ 1 > m_buff.size()){
                qDebug()<<"pkg is less than given size.";
                m_noise++;
                m_mutex.lock();
                m_buff.removeFirst();
                m_mutex.unlock();
                continue;
            }else{
                break;
            }
        }else{
            //如果前两个不是0xAA 0xAA就向后移一位
            m_noise++;

            m_mutex.lock();
            m_buff.removeFirst();
            m_mutex.unlock();
        }
    }
}

//使用状态机解析原始数据
int DataParser::parsePkg(const QByteArray ba, bool &raw, struct _eegPkt &pkt)
{
    m_total++;//输入的数据ba只包含一个有效包
    raw=false;//此数据包是否包含原始数据

    if(ba.isEmpty()) return -1;//如果没有数据就直接退出

    QByteArray buff = ba;//将数据添加到处理缓冲区

    /////////////////处理开始/////////////////////////////////////
    int cnt=0;
    uchar state=PARSER_STATE_SYNC;
    uchar payloadLength=0;
    uchar payloadSum=0;
    while(buff.size()){
        //状态机处理
        switch(state){
        case PARSER_STATE_SYNC://第一个同步字节
            if((uchar)buff[0]==PARSER_SYNC_BYTE){
                state=PARSER_STATE_SYNC_CHECK;
            }
            buff.remove(0,1);
            break;
        case PARSER_STATE_SYNC_CHECK:
            if((uchar)buff[0]==PARSER_SYNC_BYTE){//包第二个0xaa
                state=PARSER_STATE_PAYLOAD_LENGTH;//准备解析负载长度
                buff.remove(0,1);
            }
            break;
        case PARSER_STATE_PAYLOAD_LENGTH:
            payloadLength=(uchar)buff[0];//接下来是长度
            if(payloadLength>=170){//如果长度大于170就丢弃此包并查找下一个0xaa 0xaa
                qDebug()<<"this package payloadLength(the 3rd value) is wrong";
                state = PARSER_STATE_SYNC;
                //如果是0xaa 0xaa 0xff，包头对了但是长度不对
            }else{
                state=PARSER_STATE_CHKSUM;//准备解析有效数据
            }
            buff.remove(0,1);
            break;
        case PARSER_STATE_CHKSUM:
        {
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
                payloadSum+=(uchar)buff[j];
            }
            payloadSum &= 0xff;
            payloadSum = ~payloadSum & 0xff;

            if(payloadSum!=(uchar)buff[payloadLength]){
                //如果与校验值不同就丢弃此包数据
                m_loss++;
                qDebug()<<"Checksum failed.";
                return -1;
            }
            state=PARSER_STATE_PAYLOAD;
            //到此可以正常解析数据了
            break;
        }
        case PARSER_STATE_PAYLOAD://解析数据
        {
            if(cnt==payloadLength){
                buff.remove(0,1);//如果数据已经没了，那么还剩下一个校验值
                break;
            }
            if((uchar)buff[0]==0x01){//电源值，最大为127
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    state = PARSER_STATE_SYNC;
                    break;
                }
                pkt.power=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x02){//数据信号强度值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    state = PARSER_STATE_SYNC;
                    break;
                }
                pkt.signal=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x03){//ego上的心跳强度0-255
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    state = PARSER_STATE_SYNC;
                    break;
                }
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x04){//注意力值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    state = PARSER_STATE_SYNC;
                    break;
                }
                pkt.attention=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x05){//冥想值
                //如果缓冲区大小小于2位
                if(buff.size() < 2){
                    state = PARSER_STATE_SYNC;
                    break;
                }
                pkt.meditation=(uchar)buff[1];
                state=PARSER_STATE_PAYLOAD;
                buff.remove(0,2);
                cnt+=2;
            }else if((uchar)buff[0]==0x06){//8bit raw value
            }else if((uchar)buff[0]==0x07){
                //raw_marker 固定值为0
            }else if((uchar)buff[0]==0x80 && (uchar)buff[1]==0x02){//16位原始数据
                if(buff.size() < 5){//如果缓冲区大小小于5位
                    raw = false;
                    state = PARSER_STATE_SYNC;
                    break;
                }
                m_rawCnt++;
                raw=true;
                short rawValue=((uchar)buff[2]<<8)|(uchar)buff[3];
                m_rawData.append(rawValue);
                buff.remove(0,5);//4个数据以及最后的校验值
                break;
            }else if((uchar)buff[0]==0x81 && (uchar)buff[1]==0x20){
                //eeg_power 8个大端四字节
            }else if((uchar)buff[0]==0x83 && (uchar)buff[1]==0x18){//eeg数据部分
                //0x83标志eeg部分开始，下一位表示为eeg部分程度默认为0x18,8个大端三字节
                if(buff.size() < 26){//如果缓冲区大小小于24位
                    state = PARSER_STATE_SYNC;
                    break;
                }
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

    return 0;
}

void DataParser::run()
{
    while(1){
        if(m_buff.size()>0){
            skipInvalidByte();
            //这里用while是考虑缓冲区可能有不止一个包
            while(m_buff.size()>=6){
                //跳过无效字节
                skipInvalidByte();
                if(m_buff.size()==0) continue;
                if(((uchar)m_buff[0]!=0xaa) && ((uchar)m_buff[1]!=0xaa)){
                    continue;
                }

                //第3个字节是长度
                int length = (uchar)m_buff[2];
                assert(length>0);
                QByteArray tmpBA = m_buff.mid(0,length+2+1+1);

                //从缓冲区删除已经解析的包
                m_mutex.lock();
                m_buff.remove(0,length+4);
                m_mutex.unlock();

                //解析函数一次只解析一个包
                bool raw=false;
                struct _eegPkt pkt;
                pkt.init();
                if(parsePkg(tmpBA,raw,pkt)!=0){
                    qDebug()<<"Cannot parse data.";
                    //错误数据已经从缓存区删除，直接进行下一次解析
                }
                if(!raw){
                    pkt.noise = m_noise;
                    pkt.total = m_total;
                    pkt.loss = m_loss;
                    pkt.rawCnt = m_rawCnt;
                    pkt.raw = m_rawData;
                    m_rawData.clear();
                    emit sigNewPkt(pkt);
                }
            }//while
        }
        // NOTE 此处值不能过小，否则会造成界面假死
        QThread::msleep(15);
    }
}

//收到数据后填充至缓存区等待解析
void DataParser::sltRcvData(QByteArray ba)
{
    if(file.isOpen()){
        file.write(ba);
    }
    // NOTE DEBUG模式下，以下代码可能会崩溃
    m_mutex.lock();
    m_buff.append(ba);
    m_mutex.unlock();
}
