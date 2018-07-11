/*
20180705
2.3.4 添加QT设计师界面类
*/

#include <QApplication>
#include "hellodialog.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    HelloDialog w;
    w.show();
    return a.exec();
}
