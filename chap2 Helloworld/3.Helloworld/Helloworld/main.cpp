/*
20180705
从空项目创建Helloworld工程，实现Helloworld功能
*/
#include <QApplication> //头文件，QT中每个类都有一个与其同名的头文件
#include <QDialog>
#include <QLabel>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    QDialog w;
    w.resize(400, 300);
    QLabel label(&w);
    label.move(120, 120);
    label.setText(QObject::tr("Hello world!你好QT!"));
    w.show();
    return a.exec();
}
