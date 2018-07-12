#include "receiver.h"
#include "ui_receiver.h"
#include <QtNetwork>

Receiver::Receiver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);
    //udpreceiver
    receiver = new QUdpSocket(this);
    receiver->bind(45454, QUdpSocket::ShareAddress);    //绑定IP和端口
    connect(receiver, &QUdpSocket::readyRead,           //每当有数据报上来时，QUdpSocket就会发射readyRead信号
            this, &Receiver::processPendingDatagram);
}

Receiver::~Receiver()
{
    delete ui;
}

//槽
void Receiver::processPendingDatagram()
{
    //拥有等待的数据报
    while(receiver->hasPendingDatagrams())  //判断是否还有等待读取的数据报
    {
        QByteArray datagram;
        //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        //接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());
        ui->label->setText(datagram);
    }
}
