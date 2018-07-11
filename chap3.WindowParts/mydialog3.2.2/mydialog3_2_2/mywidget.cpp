#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDialog>
#include "mydialog.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //关联信号和槽的方法1
    //connect(ui->showChildButton, &QPushButton::clicked, this, &MyWidget::showChildDialog);
    //关联信号和槽的方法2


}

MyWidget::~MyWidget()
{
    delete ui;
}

//void MyWidget::showChildDialog()  //改用下面名称，以便使信号和槽自动关联
void MyWidget::on_showChildButton_clicked()
{
    QDialog * dialog = new QDialog(this);
    dialog->show();
}

void MyWidget::on_pushButton_2_clicked()
{
    close();
}

//add by sunzhong 20180706
void MyWidget::on_pushButton_clicked()
{
    //先关闭主界面，其实它是隐藏起来了，并没有真正退出。然后新建MyDialog对象
    close();
    MyDialog dlg;
    //如果按下了“进入主窗口”按钮，则再次显示主界面
    //否则，因为因为现在已经没有显示的界面了，所以程序退出
    if(dlg.exec() == QDialog::Accepted)
        show();
}

//end of add

