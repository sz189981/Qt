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
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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









