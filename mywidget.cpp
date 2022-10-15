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

