#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>


MyLineEdit::MyLineEdit(QWidget * parent):
    QLineEdit(parent)
{

}

//事件
bool MyLineEdit::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
        qDebug()<<tr("MyLineEdit的event()函数");
    return QLineEdit::event(event); //执行QLineEdit类的event()函数的默认操作
}

//键盘按下事件处理函数
void MyLineEdit::keyPressEvent(QKeyEvent * event)
{
    qDebug()<<tr("MyLineEdit键盘按下事件");
    QLineEdit::keyPressEvent(event);    //执行QLineEdit类的默认事件处理
    event->ignore();    //忽略该事件，以便widget类中的keyPressEvent函数也能实行
}
