/*
18.4 tcpclient2
大型文件传输，显示进度
*/

#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();

    return a.exec();
}
