#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

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
    void on_pushBtn1_toggled(bool checked);
    void on_checkBox_4_clicked();

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
