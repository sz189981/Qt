#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

//确定按钮
void MyDialog::on_pushButton_clicked()
{
    int value = ui->spinBox->value();   //获取输入的数值
    emit dlgReturn(value);              //发射信号
    //使用emit发射信号后，会立即执行槽，等槽执行完了以后，才会执行emit后面的代码
    close();                            //关闭对话框
}
