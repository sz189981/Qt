#include "mywidget.h"
#include "ui_mywidget.h"
#include <QHBoxLayout>  //基本布局管理器
#include <QGridLayout>  //栅格布局管理器
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //add by sunzhong 20180707
    //1.基本布局管理器QBoxLayout
#if 0
    QHBoxLayout * layout = new QHBoxLayout; //新建水平布局管理器
    layout->addWidget(ui->fontComboBox);    //向水平布局管理器中添加部件
    layout->addWidget(ui->textEdit);
    layout->setSpacing(50);                 //设置部件间的间隔
    layout->setContentsMargins(50, 50, 50, 50);  //设置布局管理器到边界的距离
                                                //4个参数分别是左上右下
    setLayout(layout);                      //将这个布局管理器设置为MyWidget类的布局
#endif
    //2.栅格布局管理器QGridLayout
#if 0
    QGridLayout * layout = new QGridLayout;
    //添加部件，从第0行0列开始，占据1行2列
    layout->addWidget(ui->fontComboBox, 0, 0, 1, 2);
    //添加部件，从第0行2列开始，占据1行1列
    layout->addWidget(ui->pushButton, 0, 2, 1, 1);
    //添加部件，从第1行0列开始，占据1行3列
    layout->addWidget(ui->textEdit, 1, 0, 1, 3);
    setLayout(layout);
    //end of add
#endif
    ui->textEdit->hide();   //让文本编辑器隐藏
}

MyWidget::~MyWidget()
{
    delete ui;
}



void MyWidget::on_textEdit_textChanged()
{
    QString str = ui->textEdit->toPlainText();
    qDebug()<<tr("输入：")<<str;
}

//扩展/隐藏窗口
void MyWidget::on_pushButton_toggled(bool checked)
{
    ui->textEdit->setVisible(checked);  //设置文本编辑器的显示和隐藏
    if(checked)
        ui->pushButton->setText(tr("隐藏可扩展窗口"));
    else
        ui->pushButton->setText(tr("显示可扩展窗口"));
}
