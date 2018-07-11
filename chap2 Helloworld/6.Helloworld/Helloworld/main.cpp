/*
20180705
自定义C++类hellodialog
*/
#include <QApplication>
#include "hellodialog.h"    //新建的HelloDialog类的头文件

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    HelloDialog w;          //定义该类的对象
    w.show();
    return a.exec();
}
