/*
20180712 基于Qt Creator 4.4.1 Based on Qt 5.9.3 (MSVC 2015, 32 bit)
按照网上教程：
Qt从零开始制作串口调试助手-（第一章、工程文件建立）-Creator_Ly
从头敲代码，实现在Qt5上的串口工具

第一章、工程文件建立
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
