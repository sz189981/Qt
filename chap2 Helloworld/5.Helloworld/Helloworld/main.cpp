/*
20180705
从空项目创建Helloworld工程，实现Helloworld功能
+基于3.Helloworld，用Qt添加ui，替代原来的代码ui；
*/
//#include <QApplication> //头文件，QT中每个类都有一个与其同名的头文件
//#include <QDialog>
//#include <QLabel>
#include "ui_hellodialog.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    QDialog w;
    //w.resize(400, 300);
    //QLabel label(&w);
    //label.move(120, 120);
    //label.setText(QObject::tr("Hello world!你好QT!"));
    Ui::HelloDialog ui;
    ui.setupUi(&w);
    w.show();
    return a.exec();
}
