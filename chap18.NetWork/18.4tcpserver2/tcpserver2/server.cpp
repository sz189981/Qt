#include "server.h"
#include "ui_server.h"
#include <QtNetwork>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    //tcpserver传输 文件
    connect(&tcpServer, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));
}

Server::~Server()
{
    delete ui;
}

//监听槽的实现
void Server::start()
{
    if(! tcpServer.listen(QHostAddress::LocalHost, 6666))
    {
        qDebug()<<tcpServer.errorString();
        close();
        return;
    }
    ui->startButton->setEnabled(false);
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    ui->serverStatusLabel->setText(tr("监听"));
    ui->serverProgressBar->reset();
}

//接收连接槽
void Server::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()),
            this, SLOT(updateServerProgress()));

    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->serverStatusLabel->setText(tr("接受连接"));
    //关闭服务器，不再监听
    tcpServer.close();
}

//更新进度条槽，文件接收实际工作
void Server::updateServerProgress()
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_0);
    //如果接收到的数据小于16字节，保存到来的文件头结构
    if(bytesReceived < sizeof(qint64)*2)
    {
        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
           //接收数据总大小信息和文件名大小信息
            in>>totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }

        if((tcpServerConnection->bytesAvailable() >= fileNameSize) && (fileNameSize != 0))
        {
            //接收文件名，并建立文件
            in >> fileName;
            ui->serverStatusLabel->setText(tr("接收文件%1...").arg(fileName));
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if(! localFile->open(QFile::WriteOnly))
            {
                qDebug()<<"server:open file error!";
                return;
            }
            else
            {
                return;
            }
        }
    }
    //如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->serverProgressBar->setMaximum(totalBytes);
    ui->serverProgressBar->setValue(bytesReceived);
    //接收数据完成时
    if(bytesReceived == totalBytes)
    {
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(tr("接收文件%1成功！").arg(fileName));
    }
}

//显示错误槽
void Server::displayError(QAbstractSocket::SocketError sockerError)
{
    qDebug()<<tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(tr("服务器就绪!"));
    ui->startButton->setEnabled(true);
}

//开始监听键信号槽
void Server::on_startButton_clicked()
{
    start();
}













