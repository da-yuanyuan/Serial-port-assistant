#include <functional>
#include <chrono>
#include <QSerialPortInfo>
#include <QDebug>

#include "serialport.h"

SerialPort::SerialPort() : state(true) {}

SerialPort::~SerialPort()
{
    state = false;
    find_port_thread.join();
}

int SerialPort::init()
{
    state = true;
    return 0;
}

int SerialPort::find_available_ports()
{
    qDebug("aaa");
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
