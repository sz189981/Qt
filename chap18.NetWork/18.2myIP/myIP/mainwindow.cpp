#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add by sunzhong 20180711 for IP
    QString localHostName = QHostInfo::localHostName();     //获取本地主机名称
    QHostInfo info = QHostInfo::fromName(localHostName);    //获取与主机名相关的IP地址列表
    qDebug()<<"localHosName:"<<localHostName<<endl
           <<"IP Address:"<<info.addresses();
    foreach(QHostAddress address, info.addresses())     //遍历获取IPv4地址
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug()<<address.toString();
    }
    /****************************************/
    //对百度IP进行查找，查找完成后调用lookedUp槽q
    QHostInfo::lookupHost("www.baidu.com", this, SLOT(lookedUp(QHostInfo)));
    /****************************************/
    //QNetworkInterface类获取主机IP地址列表和网络接口信息
    //获取所有网络接口的列表
    QList <QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //遍历每一个网络接口
    foreach(QNetworkInterface interface, list)
    {
        //接口名称
        qDebug()<<"Name: "<<interface.name();
        //硬件地址
        qDebug()<<"HardwareAddress: "<<interface.hardwareAddress();
        //获取IP地址条目列表，每个条目包含一个IP地址、子网掩码和广播地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        //遍历每个IP地址条目
        foreach(QNetworkAddressEntry entry, entryList)
        {
            //IP地址
            qDebug()<<"IP地址："<<entry.ip().toString();
            //子网掩码
            qDebug()<<"Netmask:"<<entry.netmask().toString();
            //广播地址
            qDebug()<<"Broadcast:"<<entry.broadcast().toString();
        }
    }
    /*******************************************/
    //通过QDnsLookup类进行Dns查询
    //end of add

}

MainWindow::~MainWindow()
{
    delete ui;
}

//lookedUp槽的定义
void MainWindow::lookedUp(const QHostInfo &host)
{
    if(host.error() != QHostInfo::NoError)
    {
        qDebug()<<"Lookup failed:"<<host.errorString();
        return;
    }
    foreach(const QHostAddress &address, host.addresses())
        qDebug()<<"Found Address:"<<address.toString();
}

