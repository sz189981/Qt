#include "ComDialog.h"
#include "ui_ComDialog.h"

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
    //7.1(4)同理将“串口配置界面”和“关于界面”设置窗口标题
    //设置窗口标题
    setWindowTitle(tr("串口配置"));
}

ComDialog::~ComDialog()
{
    delete ui;
}
