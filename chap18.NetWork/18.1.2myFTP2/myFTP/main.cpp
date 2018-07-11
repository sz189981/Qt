/*
18.1.2 FTP
QFtp类的使用
在窗口看到下载文件的内容
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
