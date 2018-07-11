#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qftp.h"
#include <QTextCodec>
#include <QFile>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add by sunzhong 20180711 for 浏览并下载FTP服务器上所有文件
    ui->progressBar->setValue(0);
    connect(ui->fileList, &QTreeWidget::itemActivated,  //单击或双击都会发射itemActivated信号
            this, &MainWindow::processItem);
    //end of add
}

MainWindow::~MainWindow()
{
    delete ui;
}

//槽的定义
void MainWindow::on_connectButton_clicked()
{
    ui->fileList->clear();
    currentPath.clear();
    isDirectory.clear();
    ui->progressBar->setValue(0);

    ftp = new QFtp(this);
    connect(ftp, &QFtp::commandStarted,
            this, &MainWindow::ftpCommandStarted);
    connect(ftp, &QFtp::commandFinished,
            this, &MainWindow::ftpCommandFinished);
    connect(ftp, &QFtp::listInfo,           //listInfo信号在执行完list命令时发射
            this, &MainWindow::addToList);
    connect(ftp, &QFtp::dataTransferProgress,
            this, &MainWindow::updateDataTransferProgress);

    QString ftpServer = ui->ftpServerLineEdit->text();
    QString userName  = ui->userNameLineEdit->text();
    QString passWord  = ui->passWordLineEdit->text();
    ftp->connectToHost(ftpServer, 21);
    ftp->login(userName, passWord);
}

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
            file->close();
        }
        ui->downloadButton->setEnabled(true);
    }
    else if(ftp->currentCommand() == QFtp::List)
    {
        if(isDirectory.isEmpty())
        {
            ui->fileList->addToLevelItem(new QTreeWidgetItem(QStringList()<<tr("<empty>")));
            ui->fileList->setEnabled(false);
            ui->label->setText(tr("该目录为空"));
        }
    }
    else if(ftp->currentCommand() == QFtp::Close)
    {
        ui->label->setText(tr("已经关闭连接"));
    }
}

















