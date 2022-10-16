#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "serialport.h"
#include "senderr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget, public PortsListener
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void update_ports(QStringList names) override;
    void update_recvdata(QString data) override;
private slots:
    void on_open_Bt_clicked();

    void on_close_Bt_clicked();

    void on_send_Bt_clicked();

    void on_clean_Bt_clicked();

private:
    Ui::MyWidget *ui;
    senderr* m_senderr_win;
};

#endif // MYWIDGET_H
