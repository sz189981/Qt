/*
20180706
第三章对话框类QDialog_3.2.2多窗口切换(信号和槽)
1、使用connect关联信号和槽
2、通过修改槽的名称，自动关联信号
*/

#include "mywidget.h"
#include <QApplication>
#include "mydialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    MyDialog dialog;
    if(dialog.exec() == QDialog::Accepted)  //判断dialog执行结果
    {
        w.show();   //按下“进入主界面”按钮，则显示主界面
        return a.exec();
    }
    else
        return 0;   //否则退出程序
}
