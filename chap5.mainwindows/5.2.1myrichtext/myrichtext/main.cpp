/*
5.2.1富文本文档结构
5.2.2文本块
5.2.3表格、列表和图片
5.2.4查找功能
5.2.5语法高亮与HTML
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
