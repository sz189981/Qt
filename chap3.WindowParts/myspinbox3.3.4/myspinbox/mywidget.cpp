#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //1.QDataTimeEdit
    //设置事件为当前系统时间
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    //设置时间的显示格式
    ui->dateTimeEdit->setDisplayFormat(tr("yyyy年MM月dd日 HH时mm分ss秒"));
    qDebug()<<tr("Current time:")<<ui->dateTimeEdit->text();
    qDebug()<<tr("current time:")<<ui->dateTimeEdit->dateTime();

}

MyWidget::~MyWidget()
{
    delete ui;
}

//2.QSpinBox和QDoubleSpinBox
void MyWidget::on_spinBox_valueChanged(int arg1)
{
    qDebug()<<tr("QSpinBox1:")<<arg1;
    qDebug()<<tr("QSpinBox2:")<<ui->spinBox->value();
}

void MyWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    qDebug()<<tr("QDoubleSpinBox1:")<<arg1;
    qDebug()<<tr("QDoubleSpinBox2:")<<ui->doubleSpinBox->value();
}
