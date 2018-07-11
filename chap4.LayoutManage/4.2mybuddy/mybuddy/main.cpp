/*
4.2设置伙伴(buddy)
4.3设置Tab键顺序
4.4Qt Creator中的定位器
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
