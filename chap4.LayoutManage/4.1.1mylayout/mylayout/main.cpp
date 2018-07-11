/*
4.1.1布局管理器
4.1.2设置部件大小
4.1.3可扩展窗口
*/

#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}
