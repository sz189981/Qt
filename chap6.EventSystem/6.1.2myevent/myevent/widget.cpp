#include "widget.h"
#include "ui_widget.h"
//6.1.2事件的传递
#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //6.1.2 事件的传递
    lineEdit = new MyLineEdit(this);
    lineEdit->move(100, 100);

    //事件过滤器等其他方法获取事件的顺序
    lineEdit->installEventFilter(this); //在Widget上为lineEdit安装事件过滤器

}

Widget::~Widget()
{
    delete ui;
}

//事件处理函数的定义
void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<tr("Widget键盘按下事件");

}

//事件过滤器函数的定义
bool Widget::eventFilter(QObject * obj, QEvent *event)
{
    if(obj == lineEdit) //如果是lienEdit部件的事件
    {
        if(event->type() == QEvent::KeyPress)
            qDebug()<<tr("Widget的事件过滤器");

    }
    return QWidget::eventFilter(obj, event);
}













