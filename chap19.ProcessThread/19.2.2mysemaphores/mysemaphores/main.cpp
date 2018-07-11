/*
19.2.2 同步线程
QSemaphore
*/
#include <QtCore>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

const int DataSize = 10;
const int BufferSize = 5;
char buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

//生产者类
class Producer:public QThread
{
public:
    void run();
};

void Producer::run()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < DataSize; ++i)
    {
        freeBytes.acquire();
        buffer[i%BufferSize] = "ACGT"[(int)qrand()%4];
        qDebug()<<QString("producer:%1").arg(buffer[i%BufferSize]);
        usedBytes.release();
    }
}

//消费者类
class Consumer:public QThread
{
public:
    void run();
};

void Consumer::run()
{
    for(int i = 0; i < DataSize; ++i)
    {
        usedBytes.acquire();    //获取一个使用的字节
        qDebug()<<QString("consumer:%1").arg(buffer[i%BufferSize]);
        freeBytes.release();    //释放一个空闲字节
    }
}

//主程序
int main(int argc, char * argv[])
{
    QCoreApplication app(argc, argv);
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();

    producer.wait();
    consumer.wait();

    return app.exec();
}





