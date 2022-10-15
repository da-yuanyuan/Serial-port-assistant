#include "mywidget.h"
#include "serialport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();
    SerialPort::get_serialport().init();
    SerialPort::get_serialport().find_available_ports();
    SerialPort::get_serialport().add_listen(&w);
    return a.exec();
}
