#include "myaction.h"
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>

void MyAction::sendText()
{
    emit getText(lineEdit->text()); //发射信号，将行编辑器中内容发射出去
    lineEdit->clear();              //清空行编辑器中的内容
}

MyAction::MyAction(QObject *parent) : QWidgetAction(parent)
{
    //创建行编辑器
    lineEdit = new QLineEdit;
    //将行编辑器的按下回车键和发送文本槽关联
    connect(lineEdit, &QLineEdit::returnPressed,
            this, &MyAction::sendText);
}

//
QWidget * MyAction::createWidget(QWidget * parent)
{
    //这里使用inherits()函数判断父部件是否是菜单或工具栏
    //如果是，则创建该父部件的子部件，并返回子部件
    //如果不是，则直接返回0
    if(parent->inherits("QMenu") || parent->inherits("QToolBar"))
    {
        QSplitter * splitter = new QSplitter(parent);
        QLabel * label = new QLabel;
        label->setText(tr("插入文本："));
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }
    return 0;
}
