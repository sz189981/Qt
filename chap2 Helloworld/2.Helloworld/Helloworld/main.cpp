#include "hellodialog.h"
#include <QApplication>

/*
20180705
用Qt Widgets Application创建Hello world项目
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloDialog w;
    w.show();

    return a.exec();
}
