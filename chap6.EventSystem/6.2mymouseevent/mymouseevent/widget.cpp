#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
//#include <QWindowStateChangeEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QCursor cursor;                         //创建光标对象
    cursor.setShape(Qt::OpenHandCursor);    //设置光标形状
    setCursor(cursor);                      //使用光标
    setMouseTracking(true);                 //设置鼠标跟踪
}

Widget::~Widget()
{
    delete ui;
}

//鼠标按下事件
void Widget::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);//使鼠标指针暂时改变形状
        offset = event->globalPos() - pos();      //获取指针位置和窗口位置的差值
    }
    else if(event->button() == Qt::RightButton)
    {
        QCursor cursor(QPixmap("../mymouseevent/logo.png"));
        QApplication::setOverrideCursor(cursor);    //使用自定义的图片改变鼠标指针
    }

}

//鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent * event)
{
    if(event->buttons() & Qt::LeftButton)   //这里必须使用button()
    {
        QPoint temp;
        temp = event->globalPos() - offset;
        move(temp);     //使用鼠标指针当前位置减去差值，就得到窗口应该移动的位置
    }
}

//鼠标释放事件
void Widget::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);                        //防止event参数未使用报错
    QApplication::restoreOverrideCursor();  //恢复鼠标指针形状
}

//鼠标双击事件
void Widget::mouseDoubleClickEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(windowState() != Qt::WindowFullScreen)   //如果当前不是全屏
            setWindowState(Qt::WindowFullScreen);
        else
            setWindowState(Qt::WindowNoState);      //恢复以前的大小
    }
}


//鼠标滚轮事件
void Widget::wheelEvent(QWheelEvent * event)
{
    if(event->delta() > 0)
    {
        ui->textEdit->zoomIn();     //进行放大
    }
    else
    {
        ui->textEdit->zoomOut();    //进行缩小
    }
}













