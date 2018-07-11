#ifndef MYDIALOG1_H
#define MYDIALOG1_H

#include <QWidget>

namespace Ui {
class mydialog1;
}

class mydialog1 : public QWidget
{
    Q_OBJECT

public:
    explicit mydialog1(QWidget *parent = 0);
    ~mydialog1();

private:
    Ui::mydialog1 *ui;
};

#endif // MYDIALOG1_H
