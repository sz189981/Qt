#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if("横向" == arg1)
        qDebug()<<tr("横向");
    else
        qDebug()<<tr("纵向");
}
