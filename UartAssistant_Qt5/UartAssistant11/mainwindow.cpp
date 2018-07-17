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
第九章、串口读写数据实现
第十章、串口接收数据处理
第十一章、数据校验码生成功能
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
//7.1(3)设置编码格式
#include <QtCore/qtextcodec.h>
#include <QDebug>

#include <QFileDialog>
#include <QMessageBox>

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

    //9.12④
    P_Com->setMainUiPoint(ui);

    //6.4、mainwindow.cpp建立信号槽，将主菜单关联到信号槽中。
    //菜单栏
    connect(ui->Quit, SIGNAL(triggered()),
            this, SLOT(MainWindow_Quit()));
    connect(ui->About, SIGNAL(triggered()),
            this, SLOT(MainWindow_About()));
    connect(ui->Communating, SIGNAL(triggered()),
            this, SLOT(MainWindow_Communating()));
    //10.1(4)初始化勾选框
    //参数初始化
    ui->HexReceive->setChecked(false);
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

//10.1十六进制显示
//⑵添加是否16进制显示槽函数，选择toggled(bool)
//⑶添加16进制显示标志位处理程序
void MainWindow::on_HexReceive_toggled(bool checked)
{
    qDebug()<<"mainwindow:checked:"<<checked;
    P_Com->setIsHexDisplay(checked);
}

//10.2(5)主界面添加停止显示标志处理函数
void MainWindow::on_ReceiveStop_clicked(bool checked)
{
    if(checked)
    {
        ui->ReceiveStop->setText(tr("继续"));
        DisplayFlag = false;
    }
    else
    {
        ui->ReceiveStop->setText(tr("停止"));
        DisplayFlag = true;
    }
    P_Com->WorkSetDisplayFlag(DisplayFlag);
}

//10.3、清除数据
//⑴添加清除数据槽函数，选择clicked()。
//⑵添加清除数据处理程序。
void MainWindow::on_ReceiveClear_clicked()
{
    ui->ReceiveDatatextBrowser->setText("");
}

//10.4 保存数据
//(1)添加数据保存槽,选择clicked()
//⑶①添加数据保存处理程序
void MainWindow::on_ReceiveSave_clicked()
{
    SaveAs();
}

//10.4⑶③添加数据保存处理程序
bool MainWindow::SaveAs()
{
    QString curFile;
    QString fileName =
    QFileDialog::getSaveFileName(this, tr("另存为"),
                                 curFile, tr("TXT文档(*.txt);;所有文件(*.*)*"));
    if(fileName.isEmpty())
    {
        return false;
    }
    if(!(fileName.endsWith(".txt", Qt::CaseInsensitive)))
    {
        fileName += ".txt";
    }
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("critical"),
                              tr("无法写入数据！"), QMessageBox::Yes);
        return false;
    }
    else
    {
        QTextStream out(&file);
        out<<ui->ReceiveDatatextBrowser->toPlainText(); //移入out/file
        return true;
    }
}

//11.6、添加“求SUM”处理程序。
void MainWindow::on_SendDataSUM_clicked()
{
    uint8_t SumResult, SendBuf[200];    //最大输入字符数
    ushort TxNum = 0;
    QString sdata = ui->SendDatatextEdit->toPlainText();  //读取文本框数据

    if(sdata.isEmpty()) return;

    QByteArray temp;
    temp = QByteArray::fromHex(sdata.toLatin1().data());    //输入的数据为16进制，需要转化

    QDataStream out(&temp, QIODevice::ReadWrite);       //将字节数组读入

    while(! out.atEnd())
    {
        qint8 outChar = 0;
        out >> outChar;      //毎字节填充一次，知道结束
        SendBuf[TxNum] = (uint8_t)(outChar&0xff);
        TxNum++;
    }
    SumResult = (uint8_t)(myAlgorithm->Sum_Calculate(SendBuf, TxNum));

    ui->SendCRCLineEdit->setText("");       //清除原有值
    QString str = QString("%1").arg(SumResult&0xFF, 2, 16, QLatin1Char('0'));   //十六进制的转换
    str = str.toUpper();                    //转为大写
    ui->SendCRCLineEdit->insert(str);
}

//11.7、8、添加“求CRC16”槽处理程序。
void MainWindow::on_SendDataCRC16_clicked()
{
    uint8_t Crc16Result[2], SendBuf[200];   //最大输入字符串
    ushort TxNum = 0;
    QString sdata = ui->SendDatatextEdit->toPlainText();    //读取文本框数据

    if(sdata.isEmpty()) return;

    QByteArray temp;
    temp = QByteArray::fromHex(sdata.toLatin1().data());    //输入的数据为16进制，需要转换

    QDataStream out(&temp, QIODevice::ReadWrite);   //将字节数组读入

    while(! out.atEnd())
    {
        qint8 outChar = 0;
        out >> outChar;                             //毎字节填充一次，直到结束
        SendBuf[TxNum] = (uint8_t)(outChar & 0xff);
        TxNum++;
    }
    Crc16Result[0] = (uint16_t)((myAlgorithm->Crc16_Calculate(SendBuf, TxNum) & 0xFF00)>>8);
    Crc16Result[1] = (uint16_t) (myAlgorithm->Crc16_Calculate(SendBuf, TxNum) & 0x00FF);

    ui->SendCRCLineEdit->setText("");   //清除原有值
    QString str = QString("%1").arg(Crc16Result[0] & 0xFF, 2, 16, QLatin1Char('0'));   //十六进制的转换
    str = str.toUpper();
    ui->SendCRCLineEdit->insert(str);
    ui->SendCRCLineEdit->insert(" ");
    str = QString("%1").arg(Crc16Result[1]&0xFF, 2, 16, QLatin1Char('0'));  //十六进制转换
    str = str.toUpper();
    ui->SendCRCLineEdit->insert(str);


}















