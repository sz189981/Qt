#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QMenu>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->pushBtn1->setText(tr("&nihao"));    //指定了Alt+N为加速键
    ui->pushBtn2->setText(tr("帮助(&H)"));
    ui->pushBtn2->setIcon(QIcon("../mybutton/images/help.png"));
    ui->pushBtn3->setText(tr("z&oom"));
    QMenu * menu = new QMenu(this);
    menu->addAction(QIcon("../mybutton/images/zoom-in.png"), tr("放大"));
    ui->pushBtn3->setMenu(menu);


}

MyWidget::~MyWidget()
{
    delete ui;
}

//按钮是否处于按下状态
void MyWidget::on_pushBtn1_toggled(bool checked)
{
    qDebug()<<tr("按钮是否被按下：")<< checked;
}
q
void MyWidget::on_checkBox_4_stateChanged(int arg1)
{
    if(ui->checkBox_4->isChecked())
         qDebug()<<tr("被选中！")<< endl;
    else
        qDebug()<<tr("被释放")<<endl;
}
