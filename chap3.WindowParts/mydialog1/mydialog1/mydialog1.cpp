#include "mydialog1.h"
#include "ui_mydialog1.h"

mydialog1::mydialog1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mydialog1)
{
    ui->setupUi(this);
}

mydialog1::~mydialog1()
{
    delete ui;
}
