#include "ComDialog.h"
#include "ui_ComDialog.h"

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
}

ComDialog::~ComDialog()
{
    delete ui;
}
