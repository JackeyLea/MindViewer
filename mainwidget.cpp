#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_parser(new DataParser)
    , m_bStatus(false)
    , m_eType(None)
{
#ifdef Q_OS_LINUX
    qRegisterMetaType<_eegPkt>("_eegPkt");
#endif
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
    m_bStatus = true;
    ui->labelStatusValue->setText("运行");
    m_parser->setSource(COM);
    m_eType = COM;
}

void MainWidget::sltBtnSIM()
{
    m_bStatus = true;
    ui->labelStatusValue->setText("运行");
    m_parser->setSource(Sim);
    m_eType = Sim;
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
    m_bStatus = true;
    ui->labelStatusValue->setText("运行");
    m_parser->setFilePath(filePath);
    m_parser->setSource(Local);
    m_eType = Local;
}

void MainWidget::sltBtnPlay()
{
    if(m_eType == None){
        QMessageBox::warning(this,tr("警告"),tr("请先选择数据源"));
        return;
    }
    if(m_bStatus){
        QMessageBox::warning(this,tr("警告"),tr("当前处于运行状态"));
        return;
    }
    m_bStatus = true;
    ui->labelStatusValue->setText("运行");
    sltBtnClear();
}

void MainWidget::sltBtnPause()
{
    if(m_eType == None){
        QMessageBox::warning(this,tr("警告"),tr("请先选择数据源"));
        return;
    }
    if(!m_bStatus){
        QMessageBox::warning(this,tr("警告"),tr("当前处于暂停状态"));
        return;
    }
    m_bStatus = false;
    ui->labelStatusValue->setText("暂停");
}

void MainWidget::sltBtnClear()
{
    if(m_eType == None){
        QMessageBox::warning(this,tr("警告"),tr("当前无数据可清理"));
        return;
    }
    //清空界面
    ui->labelPowerValue->setText("0");
    ui->labelSignalValue->setText("0");
    ui->labelTotalCntValue->setText("0");
    ui->labelTotalLossValue->setText("0");
    ui->labelRawCntValue->setText("0");
    ui->labelNoiseValue->setText("0");
    ui->labelEEGCnt->setText("0");
    ui->frameCurve->clear();
    //清空缓存区
    m_parser->clearBuff();
}

void MainWidget::sltBtnSave()
{
    if(m_eType == None){
        QMessageBox::warning(this,tr("警告"),tr("当前无数据可保存"));
        return;
    }
    switch(m_eType){
    case COM:
        break;
    case Sim:
        QMessageBox::warning(this,tr("警告"),tr("模拟数据没必要保存"));
        break;
    case Local:
        QMessageBox::warning(this,tr("警告"),tr("你告诉我已经保存的数据怎么再保存"));
        break;
    default:
        QMessageBox::warning(this,tr("警告"),tr("没有选择源怎么保存"));
        break;
    }
}

// 从解析类中获取数据然后显示
void MainWidget::sltUpdateWidget(_eegPkt pkt)
{
    if(!m_bStatus){
        //暂停状态
        return;
    }
    ui->labelPowerValue->setText(QString("%1").arg(pkt.power));
    ui->labelSignalValue->setText(QString("%1").arg(pkt.signal));
    ui->labelTotalCntValue->setText(QString("%1").arg(pkt.total));
    ui->labelTotalLossValue->setText(QString("%1").arg(pkt.loss));
    ui->labelRawCntValue->setText(QString("%1").arg(pkt.rawCnt));
    ui->labelEEGCntValue->setText(QString("%1").arg(pkt.eegCnt));
    ui->labelNoiseValue->setText(QString("%1").arg(pkt.noise));
    ui->widgetAttention->setValue(pkt.attention);
    ui->widgetMeditation->setValue(pkt.meditation);
    ui->frameCurve->updateData(pkt);

    update();
}

