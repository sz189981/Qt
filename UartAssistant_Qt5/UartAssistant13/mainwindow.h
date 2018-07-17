#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//6.1、打开mainwindow.h，添加串口和关于子界面的头文件。
#include "Forms/AboutDialog.h"
#include "Forms/ComDialog.h"
//10.4⑵在mainwindow.h里面添加头文件#include <QtGui>，后面后调用到里面的函数。
#include <QtGui>
//11.4①、添加算法头文件和声明
#include "User/Algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //13.3关闭串口时，弹窗提示
    //关闭函数系统已经有自带的构造函数了，
    //所以我们需要从新将closeEvent函数再写一遍其执行内容即可。
    //(1)添加声明
    void closeEvent(QCloseEvent *event);        //重写虚拟关闭函数
private:
    Ui::MainWindow *ui;
    //6.2、对子界面进行对象声明
    ComDialog * P_Com;      //串口配置窗口声明
    AboutDialog * P_About;  //关于窗口声明
    //11.4②、添加算法头文件和声明
    Algorithm * myAlgorithm;    //求CRC声明

    //10.2(2)④ 停止显示
    bool DisplayFlag;

    //10.4⑶②添加数据保存处理程序
    bool SaveAs();          //另存为

    //12.2定时发送数据(1)添加定时发送时基声明
    QTimer *myTime;

    //6.5、在mainwindow.h中添加声明
private slots:
    void MainWindow_Quit();         //关闭界面
    void MainWindow_About();        //打开关于界面
    void MainWindow_Communating();  //打开串口配置界面
    //13.2(3)②添加菜单栏断开槽函数
    void MainWindow_DisCommunated();    //断开连接

    void on_ReceiveStop_clicked(bool checked);
    void on_HexReceive_toggled(bool checked);
    void on_ReceiveClear_clicked();
    void on_ReceiveSave_clicked();

    void on_SendDataSUM_clicked();
    void on_SendDataCRC16_clicked();
    void on_SendDataPush_clicked();

    //12.2(3)声明、实现定时发送槽函数①
    void SlectAutoSend();   //定时发送
    void on_AutoSend_toggled(bool checked);
    void on_HexSend_toggled(bool checked);
    void on_SendDataClear_clicked();
};

#endif // MAINWINDOW_H
















