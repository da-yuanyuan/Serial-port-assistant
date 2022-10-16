#include <QString>

#include "mywidget.h"
#include "./ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::update_ports(QStringList names)
{
    qDebug("MyWidget  update_ports");
    ui->portname_Cb->clear();
    ui->portname_Cb->addItems(names);
}

void MyWidget::update_recvdata(QString data)
{
    ui->recv_Edit->appendPlainText(data);
}

void MyWidget::on_open_Bt_clicked()
{
    if(ui->portname_Cb->count() == 0) {
        m_senderr_win = new senderr;
        m_senderr_win->setWindowTitle("error");
        m_senderr_win->set_errmsg("there is no port connected");
        //设置属性：关闭窗口时自动释放内存
        m_senderr_win->setAttribute(Qt::WA_DeleteOnClose, true);
        m_senderr_win->show();
        return;
    }

    QSerialPort::BaudRate bauRate;  //波特率
    QSerialPort::DataBits dataBits; //数据位
    QSerialPort::StopBits stopBits; //停止位
    QSerialPort::Parity check;      //校验位

    //设置波特率
    if (ui->baudrate_Cb->currentText() == "2400" ) {
        bauRate = QSerialPort::Baud2400;
    }
    if (ui->baudrate_Cb->currentText() == "4800" ) {
        bauRate = QSerialPort::Baud4800;
    }
    else if(ui->baudrate_Cb->currentText() == "9600" ) {
        bauRate = QSerialPort::Baud9600;
    }
    else if(ui->baudrate_Cb->currentText() == "115200") {
        bauRate = QSerialPort::Baud115200;
    }

    //设置数据位
    if (ui->databit_Cb->currentText() == "5") {
        dataBits = QSerialPort::Data5;
    }
    else if(ui->databit_Cb->currentText() == "6") {
        dataBits = QSerialPort::Data6;
    }
    else if(ui->databit_Cb->currentText() == "7") {
        dataBits = QSerialPort::Data7;
    }

    else if(ui->databit_Cb->currentText() == "8") {
        dataBits = QSerialPort::Data8;
    }
    //设置停止位
    if (ui->stopbit_Cb->currentText() == "1" ) {
        stopBits = QSerialPort::OneStop;
    }
    else if(ui->stopbit_Cb->currentText() == "1.5" ) {
        stopBits = QSerialPort::OneAndHalfStop;
    }
    else if(ui->stopbit_Cb->currentText() == "2" ) {
        stopBits = QSerialPort::TwoStop;
    }

    //设置校验位
    if(ui->checkbit_Cb->currentText() == "none") {
        check = QSerialPort::NoParity;
    }
    else if(ui->checkbit_Cb->currentText() == "even") {
        check = QSerialPort::EvenParity;
    }
    else if(ui->checkbit_Cb->currentText() == "odd") {
        check = QSerialPort::OddParity;
    }

    if(SerialPort::get_serialport().set_port(ui->portname_Cb->currentText(), bauRate, dataBits, stopBits, check) == true) {
        ui->open_Bt->setStyleSheet("color: rgb(255, 0, 0);");
        //TODO:串口开启成功后应禁止左侧的ComboBox选择功能
    }
    else {
        m_senderr_win = new senderr;
        m_senderr_win->setWindowTitle("error");
        m_senderr_win->set_errmsg("Please not open again");
        m_senderr_win->setAttribute(Qt::WA_DeleteOnClose, true);
        m_senderr_win->show();
    }
}

void MyWidget::on_close_Bt_clicked()
{
    SerialPort::get_serialport().close_port();
    ui->open_Bt->setStyleSheet("color: rgb(0, 0, 0);");
    //TODO:串口关闭成功后重新使能ComboBox
}

void MyWidget::on_send_Bt_clicked()
{
    if(SerialPort::get_serialport().write_port(ui->send_Edit->toPlainText()) < 0) {
        m_senderr_win = new senderr;
        m_senderr_win->setWindowTitle("error");
        m_senderr_win->set_errmsg("Please open the port first");
        //设置属性：关闭窗口时自动释放内存
        m_senderr_win->setAttribute(Qt::WA_DeleteOnClose, true);
        m_senderr_win->show();
    }
}

void MyWidget::on_clean_Bt_clicked()
{
    ui->recv_Edit->clear();
}

