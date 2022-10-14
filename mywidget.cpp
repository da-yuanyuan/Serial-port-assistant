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

void MyWidget::set_portsNameCb(const QStringList& names)
{
    ui->portname_Cb->addItems(names);
}



