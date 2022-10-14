#include "mywidget.h"

#include <QSerialPortInfo>
#include <QApplication>
#include <thread>
#include <functional>
#include <chrono>

void find_available_ports(MyWidget& wid)
{
    QStringList portName;
    while(1) {
        foreach(const QSerialPortInfo& info, QSerialPortInfo::availablePorts()) {
            portName << info.portName();
        }
        wid.set_portsNameCb(portName);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    std::thread f1(find_available_ports, std::ref(w));
    //f1.join();

    return a.exec();
}
