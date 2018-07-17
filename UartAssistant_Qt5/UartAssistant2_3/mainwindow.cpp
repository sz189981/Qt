/*
20180712 基于Qt Creator 4.4.1 Based on Qt 5.9.3 (MSVC 2015, 32 bit)
按照网上教程：
Qt从零开始制作串口调试助手-（第一章、工程文件建立）-Creator_Ly
从头敲代码，实现在Qt5上的串口工具

第一章、工程文件建立
第二章、主窗口空间添加
第三章、菜单栏和工具栏添加
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //2.编写代码方式添加菜单
    QMenu * editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));   //添加编辑菜单
    QAction * action_Open = editMenu->addAction(
            QIcon(":/image/images/open.png"),tr("打开文件(&O)"));   //添加打开菜单
    action_Open->setShortcut(QKeySequence("Ctrl+O"));         //设置快捷键
    ui->mainToolBar->addAction(action_Open);  //在工具栏中添加动作

}

MainWindow::~MainWindow()
{
    delete ui;
}
