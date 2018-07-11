#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QSharedMemory>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private:
    Ui::MyDialog *ui;
    QSharedMemory sharedMemory;
    void detach();

public slots:
    void loadFromFile();
    void loadFromMemory();

private slots:
    void on_loadFromFileButton_clicked();
    void on_loadFromSharedMemoryButton_clicked();
};

#endif // MYDIALOG_H
