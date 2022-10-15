#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <thread>
#include <list>
#include <QWidget>

class PortsListener {
public:
    virtual void update_ports(QStringList names) {}
};

class SerialPort {
public:
    static SerialPort& get_serialport() {
        static SerialPort port;
        return port;
    }
    int init();
    int find_available_ports();
    void add_listen(PortsListener* lis) {
        m_listListen.emplace_back(lis);
    }
    void remove_listen(PortsListener* lis) {
        m_listListen.remove(lis);
    }
private:
    SerialPort();
    ~SerialPort();
    std::list<PortsListener*> m_listListen;
    bool state;
    std::thread find_port_thread;
};

#endif // SERIALPORT_H
