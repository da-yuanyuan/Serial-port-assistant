#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <thread>
#include <list>
#include <memory>
#include <QWidget>
#include <QSerialPort>

class PortsListener {
public:
    virtual void update_ports(QStringList names) = 0;
    virtual void update_recvdata(QString data) = 0;
};

class SerialPort :public QWidget {
    Q_OBJECT

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
    bool set_port(QString name, QSerialPort::BaudRate baud, QSerialPort::DataBits data, QSerialPort::StopBits stop, QSerialPort::Parity check);
    int write_port(QString data);
    void close_port();
private slots:
    void serialportreadyread_slot(void);

private:
    SerialPort();
    ~SerialPort();
    std::shared_ptr<QSerialPort> m_Port;
    std::list<PortsListener*> m_listListen;
    bool state;
    std::thread find_port_thread;
};

#endif // SERIALPORT_H
