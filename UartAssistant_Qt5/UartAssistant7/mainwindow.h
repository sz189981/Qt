#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//6.1、打开mainwindow.h，添加串口和关于子界面的头文件。
#include "Forms/AboutDialog.h"
#include "Forms/ComDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //6.2、对子界面进行对象声明
    ComDialog * P_Com;      //串口配置窗口声明
    AboutDialog * P_About;  //关于窗口声明
    //6.5、在mainwindow.h中添加声明
private slots:
    void MainWindow_Quit();         //关闭界面
    void MainWindow_About();        //打开关于界面
    void MainWindow_Communating();  //打开串口配置界面
};

#endif // MAINWINDOW_H
