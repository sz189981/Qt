#ifndef HELLODIALOG_H
#define HELLODIALOG_H

//add by sunzhong 20180705
#include <QDialog>

namespace Ui {
class HelloDialog;
}
//end of add
class HelloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelloDialog(QWidget * parent = 0);
    ~HelloDialog();
private:
    Ui::HelloDialog * ui;
};

#endif // HELLODIALOG_H
