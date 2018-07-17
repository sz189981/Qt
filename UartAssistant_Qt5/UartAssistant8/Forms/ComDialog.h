#ifndef COMDIALOG_H
#define COMDIALOG_H

#include <QDialog>
//8.4(2) 声明初始化串口类
//添加头文件
#include "Qextserial/qextserialport.h"

namespace Ui {
class ComDialog;
}

class ComDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComDialog(QWidget *parent = 0);
    ~ComDialog();
    //添加声明
    QextSerialPort * myCom;
    //8.4(3) 声明定义打开串口函数
    bool WorkOpen();

private slots:
    void on_ComEnter_clicked();

private:
    Ui::ComDialog *ui;
};

#endif // COMDIALOG_H
