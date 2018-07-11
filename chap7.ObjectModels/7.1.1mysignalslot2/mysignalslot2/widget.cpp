#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //信号和槽自动关联
    QPushButton * button = new QPushButton(this);   //创建按钮
    button->setObjectName("myButton");      //指定按钮的对象名
    //
    ui->setupUi(this);      //要在定义了部件以后再调用这个函数
}

Widget::~Widget()
{
    delete ui;
}


//添加自动关联的槽
void Widget::on_myButton_clicked()
{
    close();
}








