#include "retriver.h"
#include "ui_retriver.h"

Retriver::Retriver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Retriver),
    m_pCOM(new QSerialPort),
    m_bOpen(false)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

Retriver::~Retriver()
{
    stopCOM();

    delete m_pCOM;
    delete ui;
}

//初始化界面数据并显示界面
void Retriver::showWgt()
{
    //先获取所有端口号，并显示到界面上
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        ui->comboBoxCOM->addItem(info.portName());
    }

    //设置open/close按钮名称
    if(m_bOpen){
        ui->btnOpenClose->setText("Close");
    }else{
        ui->btnOpenClose->setText("Open");
    }
    this->show();
}

void Retriver::stopCOM()
{
    if(m_pCOM->isOpen()){//如果串口已经打开就把它关闭
        m_pCOM->clear();
        m_pCOM->close();
    }
}

//读取串口中的所有数据
void Retriver::receiveData()
{
    QByteArray strData = m_pCOM->readAll();
    emit sigNewPkg(strData);//通知有原始数据来了
}

//打开关闭按钮
void Retriver::on_btnOpenClose_clicked()
{
    if(m_bOpen){//关闭串口
        stopCOM();
    }else{//打开串口
        //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
        m_pCOM->setPortName(ui->comboBoxCOM->currentText());
        //com->setPortName("/dev/pts/2");

        if(!m_pCOM->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            m_bOpen=false;
            QMessageBox::information(this,tr("Warning"),"打开失败!\n"+m_pCOM->errorString(),QMessageBox::Ok);
            return;
        }
        m_bOpen=true;
        //打开成功
        m_pCOM->setBaudRate(ui->comboBoxBaudrate->currentText().toInt(),QSerialPort::AllDirections);//设置波特率和读写方向
        m_pCOM->setDataBits((QSerialPort::DataBits)(ui->comboBoxDatabit->currentText().toInt()));		//数据位为8位
        m_pCOM->setFlowControl((QSerialPort::FlowControl)ui->comboBoxFlowControl->currentIndex());//无流控制
        m_pCOM->setStopBits((QSerialPort::StopBits)ui->comboBoxStopbit->currentText().toInt()); //一位停止位
        //无校验位
        switch (ui->comboBoxCheckbit->currentIndex()) {
        case 0:
            m_pCOM->setParity(QSerialPort::NoParity);
            break;
        case 1:
            m_pCOM->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            m_pCOM->setParity(QSerialPort::OddParity);
            break;
        case 3:
            m_pCOM->setParity(QSerialPort::SpaceParity);
            break;
        case 4:
            m_pCOM->setParity(QSerialPort::MarkParity);
            break;
        default:
            m_pCOM->setParity(QSerialPort::NoParity);
            break;
        }
        //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
        connect(m_pCOM,SIGNAL(readyRead()),this,SLOT(receiveData()));
    }
    this->close();
}

//取消操作
void Retriver::on_btnCance_clicked()
{
    stopCOM();
    this->close();
}
