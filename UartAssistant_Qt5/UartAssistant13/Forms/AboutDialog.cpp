#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //7.1(4)同理将“串口配置界面”和“关于界面”设置窗口标题
    //设置窗口标题
    setWindowTitle(tr("关于"));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
