#ifndef SENDERR_H
#define SENDERR_H

#include <QWidget>

namespace Ui {
class senderr;
}

class senderr : public QWidget
{
    Q_OBJECT

public:
    explicit senderr(QWidget *parent = nullptr);
    ~senderr();
    void set_errmsg(QString msg);
private slots:
    void on_pushButton_clicked();

private:
    Ui::senderr *ui;
};

#endif // SENDERR_H
