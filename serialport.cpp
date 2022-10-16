#include <functional>
#include <chrono>
#include <QSerialPortInfo>
#include <QDebug>
#include <QWidget>

#include "serialport.h"

using namespace std;

SerialPort::SerialPort():
state(true),
m_Port(make_shared<QSerialPort>())
{}

SerialPort::~SerialPort()
{
    state = false;
    find_port_thread.join();
}

int SerialPort::init()
{
    state = true;
    connect(m_Port.get(), SIGNAL(readyRead()), this, SLOT(serialportreadyread_slot()));
    return 0;
}

int SerialPort::find_available_ports()
{
    find_port_thread = std::thread([&] {
        QStringList portName;
        while(state) {
            if(!m_listListen.empty()) {
                QStringList curports;
                foreach(const QSerialPortInfo& info, QSerialPortInfo::availablePorts()) {
                    curports << info.portName();
                }
                if(portName != curports) {
                    portName = curports;
                    for(auto lis : m_listListen) {
                        lis->update_ports(portName);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        qDebug("find_available_ports exit");
    });
    return 0;
}

bool SerialPort::set_port(QString name, QSerialPort::BaudRate baud, QSerialPort::DataBits data, QSerialPort::StopBits stop, QSerialPort::Parity check)
{
    m_Port->setPortName(name);
    m_Port->setBaudRate(baud);
    m_Port->setDataBits(data);
    m_Port->setStopBits(stop);
    m_Port->setParity(check);
    if(m_Port->open(QIODevice::ReadWrite) == true) {
        qDebug("port %s open ok", name.toStdString().c_str());
        return true;
    }
    qDebug("port %s open falt", name.toStdString().c_str());
    return false;
}

int SerialPort::write_port(QString data)
{
    if(m_Port->write(data.toLocal8Bit().data()) == -1)
        return -1;
    return 0;
}

void SerialPort::close_port()
{
    m_Port->close();
}

void SerialPort::serialportreadyread_slot(void)
{
    QString data = QString(m_Port->readAll());
    for(auto lis : m_listListen) {
        lis->update_recvdata(data);
    }
}
