#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QWheelEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //事件过滤器
    ui->textEdit->installEventFilter(this); //为编辑器部件在本窗口上安装事件过滤器
    ui->spinBox->installEventFilter(this);

    //发送一个事件的功能
    QKeyEvent myEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);    //相当于按了一次向上键
    qApp->sendEvent(ui->spinBox, &myEvent); //发送键盘事件到spinBox部件
}

Widget::~Widget()
{
    delete ui;
}

//事件过滤器
bool Widget::eventFilter(QObject * obj, QEvent *event)
{
    if(obj == ui->textEdit)                 //判断部件
    {
        if(event->type() == QEvent::Wheel)  //判断事件
        {
            //将event强制转换为发生的事件的类型
            QWheelEvent * wheelEvent = static_cast<QWheelEvent*>(event);
            if(wheelEvent->delta()>0)
                ui->textEdit->zoomIn();
            else
                ui->textEdit->zoomOut();
            return true;                    //该事件已被处理
        }
    }
    else if(obj == ui->spinBox)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent * keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Space)
            {
                ui->spinBox->setValue(0);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
        return QWidget::eventFilter(obj, event);
}









