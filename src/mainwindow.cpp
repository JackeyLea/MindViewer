#include "mainwindow.h"
#include "ui_mainwindow.h"

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
