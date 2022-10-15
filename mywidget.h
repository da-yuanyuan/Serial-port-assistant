#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "serialport.h"

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
private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
