#include "client.h"
#include "ui_client.h"
#include <QtNetwork>
#include <QFileDialog>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //文件传输
    payloadSize = 64 * 1024;    //64KB
    totalBytes  = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpClient = new QTcpSocket(this);
    //连接服务器成功时，会发出connected信号，开始传输文件
    connect(tcpClient, SIGNAL(connected()),
            this, SLOT(startTransfer()));
    connect(tcpClient, SIGNAL(bytesWritten(qint64)),
            this, SLOT(updateClientProgress(qint64)));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SockerError)));
    ui->sendButton->setEnabled(false);
}

Client::~Client()
{
    delete ui;
}

//打开文件槽
void Client::openFile()
{
    fileName = QFileDialog::getOpenFileName(this);  //使用QFileDialog打开一个本地文件
    if(! fileName.isEmpty())
    {
        ui->sendButton->setEnabled(true);
        ui->clientStatusLabel->setText(tr("打开文件%1成功！").arg(fileName));
    }
}

//连接服务器槽
void Client::send()
{
    ui->sendButton->setEnabled(false);
    //初始化已发送字节为0
    bytesWritten = 0;
    ui->clientStatusLabel->setText(tr("连接中..."));
    //连接到服务器
    tcpClient->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
}

//文件头发送槽
void Client::startTransfer()
{
    localFile = new QFile(fileName);
    if(! localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"client : Open file error!";
        return;
    }
    //获取文件大小
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_0);
    QString currentFileName =
            fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    //保留总大小信息空间，文件名大小信息空间，然后输入文件名
    sendOut<<qint64(0)<<qint64(0)<<currentFileName;
    //这里总大小是总大小信息+文件名大小信息+文件名+实际文件大小
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);
    //返回outBolock的开始，用实际的大小信息替代两个qint64(0)空间
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));
    //发送完文件头结构后剩余数据的大小
    bytesToWrite = totalBytes - tcpClient->write(outBlock);
    ui->clientStatusLabel->setText(tr("已连接"));
    outBlock.resize(0);
}

//更新进度条槽，发送实际文件
void Client::updateClientProgress(qint64 numBytes)
{
    //已经发送数据的大小
    bytesWritten += (int)numBytes;
    //如果已经发送了数据
    if(bytesToWrite > 0)
    {
        //每次发送payloadSize大小的数据，这里设置为64KB，如果剩余不足64KB
        //就发送剩余数据的大小
        outBlock = localFile->read(qMin(bytesToWrite, payloadSize));
        //发送完一次数据后还剩余的数据大小
        bytesToWrite -= (int)tcpClient->write(outBlock);
        //清空发送缓冲区
        outBlock.resize(0);
    }
    else    //如果没有发送任何数据，则关闭文件
    {
        localFile->close();
    }
    //更新进度条
    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);
    //如果发送完毕
    if(bytesWritten == totalBytes)
    {
        ui->clientStatusLabel->setText(tr("传输文件%1成功").arg(fileName));
        localFile->close();
        tcpClient->close();
    }
}

//显示错误槽
void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpClient->errorString();
    tcpClient->close();
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(tr("客户端就绪"));
    ui->sendButton->setEnabled(true);

}

//打开按钮
void Client::on_openButton_clicked()
{
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(tr("状态：等待打开文件！"));
    openFile();
}

//发送按钮
void Client::on_sendButton_clicked()
{
    send();
}











