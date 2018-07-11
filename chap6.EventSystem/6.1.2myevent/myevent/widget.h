#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class MyLineEdit;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool eventFilter(QObject * obj, QEvent *event);

private:
    Ui::Widget *ui;

//2.1.2事件的传递
    MyLineEdit * lineEdit;
protected:
    void keyPressEvent(QKeyEvent * event);  //键盘按下事件

};

#endif // WIDGET_H
