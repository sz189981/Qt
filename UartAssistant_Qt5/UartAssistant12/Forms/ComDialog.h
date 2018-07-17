#ifndef COMDIALOG_H
#define COMDIALOG_H
#include <QDebug>

#include <QDialog>
//8.4(2) 声明初始化串口类
//添加头文件
#include "Qextserial/qextserialport.h"
//9.11、在ComDialog.h中添加Combase的头文件和声明，
//这样ComDialog.cpp就能调用Combase.h中定义的全局变量了。
#include "User/Combase.h"
//9.12、在ComDialog.h中添加ui_mainwindow的头文件和声明，
//并将main资源与com资源关联，这样ComDialog.cpp就能调用
//mainwindow.ui中的控件了。
//9.12①
#include "ui_mainwindow.h"

namespace Ui {
class ComDialog;
}

class ComDialog : public QDialog, public Combase
{
    Q_OBJECT

public:
    explicit ComDialog(QWidget *parent = 0);
    ~ComDialog();
    //添加声明
    QextSerialPort * myCom; //公共的，在mainwindow里面有用到
    //10.2(2)添加停止显示位和设置函数声明并初始化该标志位
    void WorkSetDisplayFlag(bool flag)
    {
        DisplayFlag = flag;
    }
    //8.4(3) 声明定义打开串口函数
    bool WorkOpen();

    //9.12 ③
    void setMainUiPoint(Ui::MainWindow * ui)
    {
        main_ui = ui;
    }

    //12.1手动发送数据
    //(1)在ComDialog文件中建立发送函数
    void WorkSendMessage();     //发送数据

private slots:
    void on_ComEnter_clicked();
    //9.1在ComDialog.h中添加串口读取数据函数声明
    void ReadMyCom();

private:
    Ui::ComDialog *ui;

    Ui::MainWindow *main_ui;    //9.12 ② 声明ui_mainwindow
    //10.2(2)②停止显示
    bool DisplayFlag;
};

#endif // COMDIALOG_H
