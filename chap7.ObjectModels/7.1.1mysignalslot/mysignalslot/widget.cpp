#include "widget.h"
#include "ui_widget.h"
#include "mydialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //信号和槽
    MyDialog * dlg = new MyDialog(this);
    //将对话框中的自定义信号与主界面中自定义槽进行关联
    connect(dlg, SIGNAL(dlgReturn(int)),
            this, SLOT(showValue(int)));
    dlg->show();
}

Widget::~Widget()
{
    delete ui;
}

//自定义槽
void Widget::showValue(int value)
{
    ui->label->setText(tr("获取的值是:%1").arg(value));
}
