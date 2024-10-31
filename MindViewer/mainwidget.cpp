#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_parser(new DataParser)
{
    ui->setupUi(this);
    ui->widgetAttention->setLabel("注意力");
    ui->widgetMeditation->setLabel("冥想值");

    initConn();

    //启动解析线程
    m_parser->start();
}

MainWidget::~MainWidget()
{
    delete ui;
    if(m_parser){
        if(m_parser->isRunning()){
            m_parser->requestInterruption();
            m_parser->quit();
            m_parser->wait(50);
            m_parser->deleteLater();
        }
    }
}

void MainWidget::initConn()
{
    connect(ui->btnCOM,&QPushButton::clicked,this,&MainWidget::sltBtnCOM);
    connect(ui->btnSim,&QPushButton::clicked,this,&MainWidget::sltBtnSIM);
    connect(ui->btnLocal,&QPushButton::clicked,this,&MainWidget::sltBtnLocal);
    connect(ui->btnPlay,&QPushButton::clicked,this,&MainWidget::sltBtnPlay);
    connect(ui->btnPause,&QPushButton::clicked,this,&MainWidget::sltBtnPause);
    connect(ui->btnClear,&QPushButton::clicked,this,&MainWidget::sltBtnClear);
    connect(ui->btnSave,&QPushButton::clicked,this,&MainWidget::sltBtnSave);

    connect(m_parser,&DataParser::sigNewPkt,this,&MainWidget::sltUpdateWidget);
}

void MainWidget::sltBtnCOM()
{
    m_parser->setSource(COM);
}

void MainWidget::sltBtnSIM()
{
    m_parser->setSource(Sim);
}

void MainWidget::sltBtnLocal()
{
    // 选择本地文件
    QString filePath = QFileDialog::getOpenFileName(this,tr("打开"),QString(),QString());
    if(filePath.isEmpty()){
        QMessageBox::information(this,tr("警告"),tr("未选择任何文件"),QMessageBox::Ok);
        return;
    }

    //传递参数
    m_parser->setFilePath(filePath);
    m_parser->setSource(Local);
}

void MainWidget::sltBtnPlay()
{
    QMessageBox::information(this,tr("警告"),tr("功能未实现，不要乱点"),QMessageBox::Ok);
}

void MainWidget::sltBtnPause()
{
    QMessageBox::information(this,tr("警告"),tr("功能未实现，不要乱点"),QMessageBox::Ok);
}

void MainWidget::sltBtnClear()
{
    //清空界面
    ui->labelPowerValue->setText("0");
    ui->labelSignalValue->setText("0");
    ui->labelTotalCntValue->setText("0");
    ui->labelTotalLossValue->setText("0");
    ui->labelRawCntValue->setText("0");
    ui->labelNoiseValue->setText("0");
    ui->widgetEEG->CurveClear();
    //清空缓存区
    m_parser->clearBuff();
}

void MainWidget::sltBtnSave()
{
    QMessageBox::information(this,tr("警告"),tr("功能未实现，不要乱点"),QMessageBox::Ok);
}

// 从解析类中获取数据然后显示
void MainWidget::sltUpdateWidget(_eegPkt pkt)
{
    qDebug()<<"new pkt";
    ui->labelPowerValue->setText(QString("%1").arg(pkt.power));
    ui->labelSignalValue->setText(QString("%1").arg(pkt.signal));
    ui->labelTotalCntValue->setText(QString("%1").arg(pkt.total));
    ui->labelTotalLossValue->setText(QString("%1").arg(pkt.loss));
    ui->labelRawCntValue->setText(QString("%1").arg(pkt.rawCnt));
    ui->labelNoiseValue->setText(QString("%1").arg(pkt.noise));
    ui->widgetAttention->setValue(pkt.attention);
    ui->widgetMeditation->setValue(pkt.meditation);
    ui->widgetEEG->updateData(pkt);

    update();
}

