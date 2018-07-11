#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QWizard>

//add by sunzhong 20180707 for 错误信息对话框
class QErrorMessage;
//end of add

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MyWidget *ui;
    //add by sunzhong 20180707 for 错误信息对话框
    QErrorMessage * errordlg;
    //end of add

    //add by sunzhong 20180707 for Wizard class
    QWizardPage * createPage1();    //新添加
    QWizardPage * createPage2();
    QWizardPage * createPage3();

    //end of add
};



#endif // MYWIDGET_H
