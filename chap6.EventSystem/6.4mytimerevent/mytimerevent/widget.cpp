#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>

//定时器溢出信号槽定义
void Widget::timerUpdate()
{
    //电子表显示
    QTime time = QTime::currentTime(); //获取当前时间
    QString text = time.toString("hh:mm:ss");  //转换为字符串
    if((time.second()%2) == 0)
        text[2] = ' ';                   //每隔1秒将：显示为空格
    ui->lcdNumber->display(text);
    //随机数使用
    int rand = qrand()%300; //产生300以内的正整数
    ui->lcdNumber->move(rand, rand);    //LCD_Number部件每隔1秒移动一个随机位置
    //开启一个只运行一次的定时器
    QTimer::singleShot(10000, this, &Widget::close); //10秒后关闭窗口
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //add by sunzhong 20180709 for定时器事件与随机数
    id1 = startTimer(1000); //开启一个1秒定时器，返回其ID
    id2 = startTimer(1500);
    id3 = startTimer(2200);
    ///////////////////////////////////
    //电子表
    QTimer * timer = new QTimer(this);  //创建一个新的定时器
    //关联定时器的溢出信号到槽上
    connect(timer, &QTimer::timeout,
            this, &Widget::timerUpdate);
    timer->start(1000);                 //设置溢出时间为1秒，并启动定时器
    ///////////////////////////////////
    //随机数的使用
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));    //为qrand()函数设置初始值

    //end of add
}

Widget::~Widget()
{
    delete ui;
}

//定时器事件处理函数的定义
void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == id1) //判断是哪个定时器
    {
        qDebug()<<"timer1";
    }
    else if(event->timerId() == id2)
    {
        qDebug()<<"timer2";
    }
    else
    {
        qDebug()<<"timer3";
    }
}




















