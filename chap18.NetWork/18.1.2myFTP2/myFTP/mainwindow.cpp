#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qftp.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add by sunzhong 20180711 for QFTP
    //登录到FTP服务器
    ftp = new QFtp(this);
    ftp->connectToHost("v0.ftp.upyun.com");
    ftp->login("qtertest/qtftptest", "pwd123456");
    ftp->get("readme.txt");
    ftp->close();
    //关联信号和槽
    connect(ftp, &QFtp::commandStarted,
            this, &MainWindow::ftpCommandStarted);  //每当开始执行一个命令时，发射commandStarted()函数命令
    connect(ftp, &QFtp::commandFinished,
            this, &MainWindow::ftpCommandFinished); //每当执行结束时，发射commandFinished函数信号
    //end of add
}

MainWindow::~MainWindow()
{
    delete ui;
}

//槽的定义
void MainWindow::ftpCommandStarted(int)
{
    int id = ftp->currentCommand();
    switch(id)
    {
        case QFtp::ConnectToHost:
            ui->label->setText(tr("正在连接到服务器..."));
            break;
        case QFtp::Login:
            ui->label->setText(tr("正在登录..."));
            break;
        case QFtp::Get:
            ui->label->setText(tr("正在下载..."));
            break;
        case QFtp::Close:
            ui->label->setText(tr("正在关闭连接..."));
    }
}

void MainWindow::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(error)
            ui->label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("连接到服务器成功"));
    }
    else if(ftp->currentCommand() == QFtp::Login)
    {
        if(error)
            ui->label->setText(tr("登录出现错误：%1").arg(ftp->errorString()));
        else
            ui->label->setText(tr("登录成功"));
    }
    else if(ftp->currentCommand() == QFtp::Get)
    {
        if(error)
            ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
        else
        {
            ui->label->setText(tr("已经下载完成"));
            QTextCodec * codec = QTextCodec::codecForLocale();
            ui->textBrowser->setText(codec->toUnicode(ftp->readAll()));
        }
    }
    else if(ftp->currentCommand() == QFtp::Close)
    {
        ui->label->setText(tr("已经关闭连接"));
    }
}




















