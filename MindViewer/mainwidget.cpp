#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    initConn();
}

MainWidget::~MainWidget()
{
    delete ui;
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

}

void MainWidget::sltBtnSave()
{

}

