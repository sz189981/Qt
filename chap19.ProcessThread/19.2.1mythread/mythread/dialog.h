#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//自定义线程
#include "mythread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_stopButton_clicked();

    void on_startButton_clicked();

private:
    Ui::Dialog *ui;
    MyThread thread;
};

#endif // DIALOG_H
