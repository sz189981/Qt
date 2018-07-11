#include "mydialog.h"
#include "ui_mydialog.h"

#include <QFileDialog>
#include <QBuffer>
#include <QDebug>


MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    //
    sharedMemory.setKey("QSharedMemoryExample");

}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::detach()
{
    if(!sharedMemory.detach())
        ui->label->setText(tr("无法从共享内存中分离！"));
}

//从文件加载图片槽的定义
void MyDialog::loadFromFile()
{
    if(sharedMemory.isAttached())
        detach();
    ui->label->setText(tr("选择一个图片文件"));
    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                                    tr("Images(*.png *.jpg)"));
    QImage image;
    if(! image.load(fileName))
    {
        ui->label->setText(tr("选择的文件不是图片，请选择图片文件！"));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    //将图片加载到共享内存中
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out<<image;
    int size = buffer.size();
    if(! sharedMemory.create(size))
    {
        ui->label->setText(tr("无法创建共享内存！"));
        return;
    }
    sharedMemory.lock();

    char * to = (char *)sharedMemory.data();
    const char * from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));

    sharedMemory.unlock();
}

//从缓存加载图片槽的定义
void MyDialog::loadFromMemory()
{
    if(! sharedMemory.attach())     //attach函数将进程连接到共享内存段
    {
        ui->label->setText(tr("无法连接到共享内存段，\n"
                              "请先加载一张图片！"));
        return;
    }
    QBuffer buffer;
    QDataStream in(&buffer);    //读取内存段中的数据

    QImage image;
    sharedMemory.lock();
    buffer.setData((char *)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in>>image;
    sharedMemory.unlock();
    sharedMemory.detach();      //detach函数将进程与共享内存段进行分离
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void MyDialog::on_loadFromFileButton_clicked()
{
    loadFromFile();
}

void MyDialog::on_loadFromSharedMemoryButton_clicked()
{
    loadFromMemory();
}












