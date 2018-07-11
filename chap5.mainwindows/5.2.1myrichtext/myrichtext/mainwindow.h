#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//add for 查找功能
class QLineEdit;
class QDialog;
//end of add
class MySyntaxHighlighter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //add for 查找功能
    QLineEdit * lineEdit;
    QDialog   * findDialog;
    //end of add
    MySyntaxHighlighter * highlighter;

private slots:
    //add by sunzhong 20180708 for 文本块
    void showTextFrame();   //遍历文档框架
    void showTextBlock();   //遍历所有文本块
    void setTextFont(bool checked); //设置字体格式
    //end of add
    //5.2.3 表格、列表与图片
    void insertTable(); //插入表格
    void insertList();  //插入列表
    void insertImage(); //插入图片

    //5.2.4 查找功能
    void textFind(); //查找文本
    void findNext(); //查找下一个


};

#endif // MAINWINDOW_H
