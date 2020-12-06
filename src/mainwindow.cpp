#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, pLocalData(new LocalData())
{
    ui->setupUi(this);

//    connect(pLocalData,&LocalData::finished,this,&MainWindow::sltParserCompleted);
}

MainWindow::~MainWindow()
{
//    if(pLocalData!=nullptr){
//        delete pLocalData;
//    }
    delete ui;
}

void MainWindow::sltParserCompleted()
{
    qDebug()<<"Local data parsered";
    //QList<pkgPacket> result = pLocalData->getParserResult();
    //qDebug()<<result.size();
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
    //调用专用函数打开解析数据
    //pLocalData->setFilePath(filePath);
    //pLocalData->start();
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

void MainWindow::on_actionCapture_triggered()
{

}

void MainWindow::on_actionSerialPort_triggered()
{

}

void MainWindow::on_actionPause_triggered()
{

}

void MainWindow::on_actionResume_triggered()
{

}

void MainWindow::on_actionClear_triggered()
{

}
