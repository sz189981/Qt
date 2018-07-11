#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPixmap>              //在标签中使用图片
#include <QMovie>                //在标签中使用GIF图片

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("华文行楷");
    font.setPointSize(20);
    font.setBold(true);         //加粗
    font.setItalic(true);       //斜体
    ui->label->setFont(font);   //使用新建的字体q

    //QString string = tr("标题太长，需要进行省略！");
    //QString str = ui->label->fontMetrics().elidedText(string, Qt::ElideRight, 180);
    //ui->label->setText(str);

    //ui->label->setPixmap(QPixmap("E:/logo.png"));   //显示图片

    QMovie * movie = new QMovie("E:/donghua.gif");
    ui->label->setMovie(movie);                     //显示动画
    movie->start();
}

MyWidget::~MyWidget()
{
    delete ui;
}
