#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add by sunzhong 20180711 for 获取网页信息
#if 0
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);
    manager->get(QNetworkRequest(QUrl("http://www.qter.org")));
#endif
    //end of add
    //add by sunzhong 20180711 for 下载文件
    manager = new QNetworkAccessManager(this);
    ui->progressBar->hide();    //初始化隐藏进度条
    //end of add
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Text Browser槽的定义
#if 0
void MainWindow::replyFinished(QNetworkReply * reply)
{
    QString all = reply->readAll();
    //qDebug()<<"network:"<<all;        //错误，什么也没打印
    ui->textBrowser->setText(all);    //正确，能显示网页内容
    reply->deleteLater();
}
#endif

//网络请求
void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url)); //发送网络请求
    connect(reply, &QNetworkReply::readyRead,   //每当有新的数据可读时，发送readyRead()信号
            this, &MainWindow::httpReadyRead);

    connect(reply, &QNetworkReply::downloadProgress,    //每当网络请求的下载进度更新时，发射downloadProgress()信号
            this, &MainWindow::updateDataReadProgress);

    connect(reply, &QNetworkReply::finished,    //每当处理结束时，发射finished()信号
            this, &MainWindow::httpFinished);

}

//槽的定义
void MainWindow::httpReadyRead()
{
    if(file)                            //先判断是否创建文件，由下载按钮单击创建的文件
        file->write(reply->readAll());  //读取返回的所有数据，然后写入到文件中
}

//设置进度条最大值和当前值
void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

//下载完成后，重新隐藏进度条，然后删除file和reply对象
void MainWindow::httpFinished()
{
    ui->progressBar->hide();
    if(file)
    {
        file->close();
        delete file;
        file = 0;
    }
    reply->deleteLater();
    reply = 0;
}

//创建本地文件，进行网络请求并显示进度条
void MainWindow::on_pushButton_clicked()
{
    //url = ui->lineEdit->text();
    QUrl url;
    url.setScheme("ftp");                   //指定FTP协议
    url.setHost("v0.ftp.upyun.com");        //设置主机地址
    url.setPath("readme.txt");              //要下载的文件路径
    url.setUserName("qtertest/qtftptest");  //用户名
    url.setPassword("pwd123456");           //密码

    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if(fileName.isEmpty())
        fileName = "index.html";
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}




