#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_timer(new QTimer)
    , m_parser(new DataParser)
{
    ui->setupUi(this);

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

}

void MainWidget::sltBtnSIM()
{

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
    ui->labelEEGPkgCnt->setText("0");
    ui->labelValue->setText("0");
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
}

