#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject * parent):QThread(parent)
{
    stopped = false;    //初始化stopped
}

//QThread 从run()函数开始执行，由start()函数调用
void MyThread::run()
{
    qreal i = 0;
    while(! stopped)
    {
        qDebug()<<QString("in MyThread:%1").arg(i);
        msleep(1000);

    }
    stopped = false;
}

void MyThread::stop()
{
    stopped = true;
}
