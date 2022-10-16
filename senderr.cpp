#include "senderr.h"
#include "ui_senderr.h"

senderr::senderr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::senderr)
{
    ui->setupUi(this);
}

senderr::~senderr()
{
    delete ui;
}

void senderr::set_errmsg(QString msg)
{
    ui->msgLb->setText(msg);
}

void senderr::on_pushButton_clicked()
{
    this->close();
}
