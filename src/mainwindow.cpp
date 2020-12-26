#include "mainwindow.h"
#include "ui_mainwindow.h"

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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionGraph->setChecked(true);
    resize(800,820);

    gen=new Generator();
    retriverWgt = new Retriver;

    connect(gen,&Generator::sendData,this,&MainWindow::sltReceiveData);
    connect(retriverWgt,&Retriver::rawData,this,&MainWindow::sltReceiveData);

    ui->graphEEG->setGeometry(0,0,800,532);
    ui->graphCommon->setGeometry(0,532,800,266);
}

MainWindow::~MainWindow()
{
    if(gen!=nullptr){
        gen->stopNow();
        delete gen;
    }
    delete retriverWgt;
    delete ui;
}

int MainWindow::parserData(QByteArray ba, bool &raw, short &rawValue, bool &eeg, struct _eegPkt &pkt)
{
    //qDebug()<<"Parsering data";
    raw=false;
    eeg=false;

    if(ba.isEmpty()) return -1;
    int size=ba.size();
    if(size>179) return -1;//官方说明最多179个字节

    int i=0;
    uchar state=PARSER_STATE_SYNC;
    uchar payloadLength;
    uchar payloadSum;
    while(i<size-1){
        switch(state){
        case PARSER_STATE_SYNC://第一个同步字节
            if((uchar)ba[i]==PARSER_SYNC_BYTE){
                //qDebug()<<"parser first aa "<<i<<(uchar)ba[i];
                state=PARSER_STATE_SYNC_CHECK;
            }
            ++i;
            break;
        case PARSER_STATE_SYNC_CHECK:
            if((uchar)ba[i]==PARSER_SYNC_BYTE){
                //qDebug()<<"parser second aa "<<i<<(uchar)ba[i];
                state=PARSER_STATE_PAYLOAD_LENGTH;//准备解析负载长度
            }else{
                state=PARSER_STATE_SYNC;
            }
            ++i;
            break;
        case PARSER_STATE_PAYLOAD_LENGTH:
            payloadLength=(uchar)ba[i];
            if(payloadLength>170){
                state=PARSER_STATE_SYNC;
                return -3;
            }else if(payloadLength==170){
                return -4;
            }else{
                payloadSum=0;
                //qDebug()<<"parser payload length "<<i<<(uchar)ba[i];
                state=PARSER_STATE_CHKSUM;//准备解析有效数据
            }
            ++i;
            break;
        case PARSER_STATE_CHKSUM:
        {
            uchar z=i;
            //首先校验数据是否有效
            for(int j=0;j<payloadLength;j++){
                //qDebug()<<(uchar)ba[z+j];
                payloadSum+=(uchar)ba[z+j];
            }
            payloadSum &= 0xff;
            payloadSum = ~payloadSum & 0xff;
            z+=payloadLength;

            if(payloadSum!=(uchar)ba[z]){
                //如果与校验值不同就丢弃此包数据
                return -1;
            }/*else{
                qDebug()<<"match";
            }*/
            //qDebug()<<"get data check sum is: "<<z<<(uchar)ba[z];
            //qDebug()<<"parser check sum "<<i;
            state=PARSER_STATE_PAYLOAD;
            break;
        }
        case PARSER_STATE_PAYLOAD://解析数据
            if((uchar)ba[i]==0x02){//数据信号强度值
                //qDebug()<<"signal value "<<i<<(uchar)ba[i]<<(uchar)ba[i+1]<<(uint)ba[i+1];
                eeg=true;
                pkt.signal=(uchar)ba[i+1];
                state=PARSER_STATE_PAYLOAD;
                i+=2;
            }else if((uchar)ba[i]==0x03){
            }else if((uchar)ba[i]==0x04){//注意力值
                //qDebug()<<"attention value "<<i<<(uchar)ba[i+1];
                eeg=true;
                pkt.attention=(uchar)ba[i+1];
                state=PARSER_STATE_PAYLOAD;
                i+=2;
            }else if((uchar)ba[i]==0x05){//冥想值
                //qDebug()<<"meditation value "<<i<<(uchar)ba[i+1];
                eeg=true;
                pkt.meditation=(uchar)ba[i+1];
                state=PARSER_STATE_PAYLOAD;
                i+=2;
                //qDebug()<<"current i "<<i<<size;
            }else if((uchar)ba[i]==0x06){//8bit raw value
            }else if((uchar)ba[i]==0x07){
            }else if((uchar)ba[i]==0x80){//16位原始数据
                //qDebug()<<"parser raw value "<<i;
                //qDebug()<<"parser a is: "<<(uchar)ba[i+2];
                //qDebug()<<"parser b is: "<<(uchar)ba[i+3];
                raw=true;
                rawValue=((uchar)ba[i+3]<<8)|(uchar)ba[i+2];
                return 0;
            }else if((uchar)ba[i]==0x81){
            }else if((uchar)ba[i]==0x83){//eeg数据部分
                //0x83标志eeg部分开始，下一位表示为eeg部分程度默认为0x18
                //qDebug()<<"parser eeg data "<<i<<ba[i];
                //qDebug()<<"parser eeg length "<<(uchar)ba[i+1];
                eeg=true;
                pkt.delta =((uint)ba[i+4]<<16)|((uint)ba[i+3]<<8)|((uint)ba[i+2]);
                pkt.theta =((uint)ba[i+7]<<16)|((uint)ba[i+6]<<8)|((uint)ba[i+5]);
                pkt.lowAlpha =((uint)ba[i+10]<<16)|((uint)ba[i+9]<<8)|((uint)ba[i+8]);
                pkt.highAlpha =((uint)ba[i+13]<<16)|((uint)ba[i+12]<<8)|((uint)ba[i+11]);
                pkt.lowBeta =((uint)ba[i+16]<<16)|((uint)ba[i+15]<<8)|((uint)ba[i+14]);
                pkt.highBeta =((uint)ba[i+19]<<16)|((uint)ba[i+18]<<8)|((uint)ba[i+17]);
                pkt.lowGamma =((uint)ba[i+22]<<16)|((uint)ba[i+21]<<8)|((uint)ba[i+20]);
                pkt.midGamma =((uint)ba[i+25]<<16)|((uint)ba[i+24]<<8)|((uint)ba[i+23]);
                state=PARSER_STATE_PAYLOAD;
                i+=26;
                //qDebug()<<(uchar)ba[i]<<i;
            }else if((uchar)ba[i]==0x86){
                break;
            }
            //ui->textHex->appendPlainText(QString::number((uchar)ba[z],16));
            break;
        case PARSER_STATE_NULL:
            break;
        default:
            break;
        }
    }

    //qDebug()<<"all data has been parsered";

    return 0;
}

void MainWindow::resizeEvent(QResizeEvent */*event*/)
{
    int width = ui->stackedWidget->width();
    int height = ui->stackedWidget->height();
    if(height <700) return;
    ui->graphEEG->setGeometry(0,0,width,height*2/3);
    ui->graphCommon->setGeometry(0,height*2/3,width,height/3);
}

void MainWindow::sltReceiveData(QByteArray ba)
{
    if(ui->actionHex->isChecked()){
        QString s;
        for(int i=0;i<ba.size();i++){
            QString ss,sss;
            sss=ss.asprintf("0x%02X ",(unsigned char)ba.at(i));
            s+=sss;
        }
        ui->textHex->appendPlainText(s);
    }else{
        bool raw,eeg;
        short rawValue;
        struct _eegPkt pkt;
        pkt.init();
        parserData(ba,raw,rawValue,eeg,pkt);
        if(eeg){
            ui->graphCommon->updateCommonData(pkt);
            ui->graphEEG->updateEEGData(pkt);
        }
        if(raw){
            ui->graphEEG->updateRawData(rawValue);
        }
    }
}

//打开文件位置
void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open"), QString());
    if (filePath.isEmpty()) {
        QMessageBox::information(this, tr("Warning"), tr("Nothing selected"));
        return;
    }
    qDebug()<<"Select file path is: "<<filePath;
}

void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg = QString("<h1>MindViewer</h1>"
                          "<h2>TGAM module tools</h2>"
                          "<h3>Author: JackeyLea</h3>"
                          "<h3>E-mail: 1768478912@qq.com</h3>"
                          "<h3>GitHub: https://github.com/JackeyLea/MindViewer</h3>"
                          "<h3>Gitee: https://gitee.com/JackeyLea/MindViewer</h3>"
                          "<h4>Do what you want but please obey the LGPL3 rules</h4>"
                          "<h4>And keep those message within application</h4>");
    QMessageBox::information(this, tr("About"), msg, QMessageBox::Ok);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionGithub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/JackeyLea/MindViewer"));
}

void MainWindow::on_actionSerialPort_triggered()
{
    retriverWgt->showWgt();
}

void MainWindow::on_actionTest_triggered()
{
    gen->start();
}

void MainWindow::on_actionSave_triggered()
{
    if(ui->actionHex->isChecked()){
        QMessageBox::information(this,tr("Save text"),"Save hex data to file?",QMessageBox::Ok|QMessageBox::Cancel);
    }else{
        QMessageBox::information(this,tr("Save image"),"Save image to file?",QMessageBox::Ok|QMessageBox::Cancel);
    }
}

void MainWindow::on_actionHex_triggered(bool checked)
{
    if(checked){
        ui->stackedWidget->setCurrentIndex(0);
        ui->actionGraph->setChecked(false);
    }else{
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionGraph->setChecked(true);
    }
}

void MainWindow::on_actionGraph_triggered(bool checked)
{
    if(checked){
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionHex->setChecked(false);
    }else{
        ui->stackedWidget->setCurrentIndex(0);
        ui->actionHex->setChecked(true);
    }
}
