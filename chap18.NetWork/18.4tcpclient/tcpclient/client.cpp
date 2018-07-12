#include "client.h"
#include "ui_client.h"
#include <QtNetwork>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //tcpclient
    tcpSocket = new QTcpSocket(this);
    //当有可读的数据时，发射readyRead信号
    connect(tcpSocket, &QTcpSocket::readyRead,
            this, &Client::readMessage);
    //当发生错误时，发射error信号
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));


}

Client::~Client()
{
    delete ui;
}

//槽的定义
void Client::newConnect()
{
    //初始化数据大小信息为0
    blockSize = 0;
    //取消已有的连接
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    //设置数据流版本
    in.setVersion(QDataStream::Qt_5_6);
    //如果刚开始接收数据
    if(blockSize == 0)
    {
        //判断接收的数据是否大于两字节，即文件大小信息所占的空间
        //如果是，则保存到blockSize变量中，否则直接返回，继续接收数据
        if(tcpSocket->bytesAvailable()<(int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    //如果没有得到全部数据，则返回，继续接收数据
    if(tcpSocket->bytesAvailable() < blockSize)
        return;
    //将接收到的数据存放到变量中
    in >> message;
    //显示接收到的数据
    ui->messageLabel->setText(message);
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
}

void Client::on_connectButton_clicked()
{
    newConnect();
}




















