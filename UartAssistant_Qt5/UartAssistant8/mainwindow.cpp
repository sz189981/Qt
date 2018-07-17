/*
20180712 基于Qt Creator 4.4.1 Based on Qt 5.9.3 (MSVC 2015, 32 bit)
按照网上教程：
Qt从零开始制作串口调试助手-（第一章、工程文件建立）-Creator_Ly
从头敲代码，实现在Qt5上的串口工具

第一章、工程文件建立
第二章、主窗口空间添加
第三章、菜单栏和工具栏添加
第四章、新建“串口配置界面”和“关于界面”
第五章、创建资源文件，并添加图片到“关于界面”
第六章、添加主界面调用子界面响应
第七章、设置窗口标题(中文）和图标
第八章、添加串口配置程序
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
//7.1(3)设置编码格式
#include <QtCore/qtextcodec.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //7.1设置窗口标题
    //(1)、用setWindowTitle函数添加英文标题
    //设置窗口标题
    //setWindowTitle(tr("UartAssistant"));
    //(2)、但是当把英文标题直接换成中文时，则会出现乱码
    //这是由于不同的编译器所使用的编码方式不一致导致的，有的使用GBK，有的使用UTF-8等。
    //(3)、所以我们只需要设置其编码格式与系统对应即可，添加相应的设置语句和头文件，如下：
    /*编码对照*/
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); //Qt5中已优化中文，此句话不需要
    /*设置窗口标题*/
    setWindowTitle(tr("串口调试助手"));






    //6.3、窗口资源建立初始化。
    P_Com = NULL;
    P_Com = new ComDialog();
    P_About = NULL;
    P_About = new AboutDialog();

    //6.4、mainwindow.cpp建立信号槽，将主菜单关联到信号槽中。
    //菜单栏
    connect(ui->Quit, SIGNAL(triggered()),
            this, SLOT(MainWindow_Quit()));
    connect(ui->About, SIGNAL(triggered()),
            this, SLOT(MainWindow_About()));
    connect(ui->Communating, SIGNAL(triggered()),
            this, SLOT(MainWindow_Communating()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

//6.6、在mainwindow.cpp中添加槽的实现函数
void MainWindow::MainWindow_Quit()
{
    this->close();
}

void MainWindow::MainWindow_About()
{
    if(P_About != NULL)
    {
        P_About->exec();    //exec会导致每次只显示一个dialog，show()函数可以同时显示多个dialog
    }
}

void MainWindow::MainWindow_Communating()
{
    if(P_Com != NULL)
    {
        P_Com->exec();
    }
}










void MainWindow::on_ReceiveSave_clicked()
{

}
