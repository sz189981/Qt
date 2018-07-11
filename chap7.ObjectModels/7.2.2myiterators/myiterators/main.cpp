/*
7.2.2 1Java风格迭代器
QList
*/


#include <QCoreApplication>
#include <QCoreApplication>
#include <QList>
#include <QListIterator>
#include <QMutableListIterator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //add by sunzhong 20180710 for Java风格迭代器
    QList <QString> list;
    list<<"A"<<"B"<<"C"<<"D";
    QListIterator<QString> i(list); //创建列表迭代器，将list作为参数
    qDebug()<<"the forwardis:";
    while(i.hasNext())              //正向遍历列表，结果为A,B,C,D
        qDebug()<<i.next();
    qDebug()<<"the backwordis:";
    while(i.hasPrevious())          //反向遍历列表，结果为D,C,B,A
        qDebug()<<i.previous();
    ////////////////////////////////////////////////
    QMutableListIterator <QString> j(list);
    j.toBack();                 //返回列表尾部
    while(j.hasPrevious())
    {
        QString str = j.previous();
        if(str == "B")
            j.remove();         //删除项目B
    }
    j.insert("Q");              //在列表最前面添加项目"Q"
    j.toBack();
    if(j.hasPrevious())
        j.previous() = "N";     //把最后一位直接赋值
    j.previous();               //跳过倒数第二位
    j.setValue("M");            //使用setValue()对上一次跳过的项目进行赋值
    j.toFront();
    qDebug()<<"the forward is:";
    while(j.hasNext())          //正向便利列表，结果为Q,A,M,N
        qDebug()<<j.next();
    //end of add
    return a.exec();
}


















