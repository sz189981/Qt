/*
5.1.1Qt资源系统、菜单栏和工具栏
5.1.2中心部件
5.1.3Dock部件
5.1.4状态栏
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
