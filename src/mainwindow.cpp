#include "mainwindow.h"
#include "ui_mainwindow.h"

/* Decoder states (Packet decoding) */
#define PARSER_STATE_NULL           0x00  /* NULL state */
#define PARSER_STATE_SYNC           0x01  /* Waiting for SYNC byte */
#define PARSER_STATE_SYNC_CHECK     0x02  /* Waiting for second SYNC byte */
#define PARSER_STATE_PAYLOAD_LENGTH 0x03  /* Waiting for payload[] length */
#define PARSER_STATE_PAYLOAD        0x04  /* Waiting for next payload[] byte */
#define PARSER_STATE_CHKSUM         0x05  /* Waiting for chksum byte */

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
    ui->actionHex->setChecked(true);

    gen=new Generator();
    connect(gen,&Generator::sendData,this,&MainWindow::sltReceiveData);
}

MainWindow::~MainWindow()
{
    if(gen!=nullptr){
        gen->stopNow();
        delete gen;
    }
    delete ui;
}

int MainWindow::parserData(QByteArray ba, struct _eegPkt &pkt)
{
    if(ba.isEmpty()) return -1;
    int size=ba.size();
    if(size>179) return -1;//官方说明最多179个字节

    int i=0;
    unsigned char state=PARSER_STATE_SYNC;
    unsigned char payloadLength;
    unsigned char payloadSum;
    //while(i<size){
    while(i<4){
        switch(state){
        case PARSER_STATE_SYNC://第一个同步字节
            if((unsigned char)ba[i]==PARSER_SYNC_BYTE){
                state=PARSER_STATE_SYNC_CHECK;
            }
            ++i;
            break;
        case PARSER_STATE_SYNC_CHECK:
            if((unsigned char)ba[i]==PARSER_SYNC_BYTE){
                state=PARSER_STATE_PAYLOAD_LENGTH;//准备解析负载长度
            }else{
                state=PARSER_STATE_SYNC;
            }
            ++i;
            break;
        case PARSER_STATE_PAYLOAD_LENGTH:
            payloadLength=ba[i];
            if(payloadLength>170){
                state=PARSER_STATE_SYNC;
                return -3;
            }else if(payloadLength==170){
                return -4;
            }else{
                payloadSum=0;
                state=PARSER_STATE_PAYLOAD;//准备解析有效数据
            }
            //qDebug()<<"payload length is: "<<payloadLength;
            ++i;
            break;
        case PARSER_STATE_PAYLOAD:
            for(int j=0;j<payloadLength;j++){
                qDebug()<<(unsigned char)ba[i+j];
                payloadSum+=ba[i+j];
            }
            payloadSum&=0xff;
            payloadSum=~payloadSum&0xff;
            i+=payloadLength;
            if(payloadSum==ba[i]){
                qDebug()<<"is match";
            }
        }
    }

    return 0;
}

void MainWindow::sltReceiveData(QByteArray ba)
{
    QString s;
    for(int i=0;i<ba.size();i++){
        QString ss,sss;
        sss=ss.asprintf("0x%02X ",(unsigned char)ba.at(i));
        s+=sss;
    }
    if(ui->actionHex->isChecked()){
        ui->textHex->appendPlainText(s);
    }
    struct _eegPkt pkt;
    parserData(ba,pkt);
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
