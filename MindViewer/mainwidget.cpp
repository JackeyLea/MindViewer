#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_timer(new QTimer)
    , m_parser(new DataParser)
{
    ui->setupUi(this);
    ui->widgetAttention->setLabel("注意力");
    ui->widgetMeditation->setLabel("冥想值");

    //定时器
    m_timer->setInterval(1000);
    m_timer->start();

    initConn();

    //启动解析线程
    m_parser->start();
}

MainWidget::~MainWidget()
{
    delete ui;
    if(m_timer){
        if(m_timer->isActive()){
            m_timer->stop();
            m_timer->deleteLater();
        }
    }
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

    connect(m_timer,&QTimer::timeout,this,&MainWidget::sltUpdateWidget);
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

}

void MainWidget::sltBtnPlay()
{

}

void MainWidget::sltBtnPause()
{

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
    //清空缓存区
    m_parser->clearBuff();
}

void MainWidget::sltBtnSave()
{

}

// 从解析类中获取数据然后显示
void MainWidget::sltUpdateWidget()
{
    //从资源池中去一个结构体
    _eegPkt pkt = m_parser->getPkg();
    ui->labelPowerValue->setText(QString("%1").arg(pkt.power));
    ui->labelSignalValue->setText(QString("%1").arg(pkt.signal));
    ui->labelTotalCntValue->setText(QString("%1").arg(pkt.total));
    ui->labelTotalLossValue->setText(QString("%1").arg(pkt.loss));
    ui->labelRawCntValue->setText(QString("%1").arg(pkt.rawCnt));
    ui->labelNoiseValue->setText(QString("%1").arg(pkt.noise));
    ui->widgetAttention->setValue(pkt.attention);
    ui->widgetMeditation->setValue(pkt.meditation);
    ui->widgetEEG->updateEEGData(pkt);

    update();
}

