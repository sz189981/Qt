#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //使主界面获得焦点
    setFocus();

    //方向键
    keyUp = false;  //初始化变量
    keyLeft = false;
    move = false;
    ui->pushButton->move(50, 100);   //斜移

}

Widget::~Widget()
{
    delete ui;
}

//键盘按下事件
void Widget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Up) //如果是向上键
    {
        if(event->isAutoRepeat())
            return;                 //按键重复时，不做处理
        keyUp = true;               //标记向上方向按键已经按下
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(event->isAutoRepeat())
            return;
        keyLeft = true;
    }
}

//按键释放事件
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        if(event->isAutoRepeat())
            return;
        keyUp = false;              //释放按键后将标志设置为false
        if(move)                    //如果已经完成了移动
        {
            move = false;           //设置标志为false
            return;
        }
        if(keyLeft)                         //如果左键按下未释放
        {
            ui->pushButton->move(30, 80);   //斜移
            move = true;                    //标记已经移动
        }
        else
        {
            ui->pushButton->move(120, 80);   //否则直接上移
        }
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(event->isAutoRepeat())
            return;
        keyLeft = false;
        if(move)
        {
            move = false;
            return;
        }
        if(keyUp)
        {
            ui->pushButton->move(30, 80);
            move = true;
        }
        else
        {
            ui->pushButton->move(30, 120);
        }
    }
    else if(event->key() == Qt::Key_Down)
    {
        ui->pushButton->move(120, 120);     //使用向下键还原按键位置
    }
}
