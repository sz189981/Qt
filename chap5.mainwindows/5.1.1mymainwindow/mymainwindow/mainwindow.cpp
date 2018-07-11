#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QLabel>
#include <QWidget>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //2.编写代码方式添加菜单
    QMenu * editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));   //添加编辑菜单
    QAction * action_Open = editMenu->addAction(
            QIcon(":/image/images/open.png"),tr("打开文件(&O)"));   //添加打开菜单
    action_Open->setShortcut(QKeySequence("Ctrl+O"));         //设置快捷键
    ui->mainToolBar->addAction(action_Open);  //在工具栏中添加动作
    //3.菜单栏
    QActionGroup * group = new QActionGroup(this);  //建立动作组
    QAction * action_L = group->addAction(tr("左对齐(&L)"));//向动作组添加动作
    action_L->setCheckable(true);                      //设置动作checkable属性为true
    QAction * action_R = group->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);
    QAction * action_C = group->addAction(tr("居中(&C)"));
    action_C->setCheckable(true);
    action_L->setChecked(true);     //最后指定action_L为选中状态
    editMenu->addSeparator();       //向菜单中添加间隔符
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);
    //4.工具栏
    QToolButton * toolBtn = new QToolButton(this);  //创建QToolButton
    toolBtn->setText(tr("颜色"));
    QMenu * colorMenu = new QMenu(this);    //创建一个菜单
    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));
    toolBtn->setMenu(colorMenu);            //添加菜单
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup); //设置弹出模式
    ui->mainToolBar->addWidget(toolBtn);    //向工具栏添加QToolButton类按钮
    QSpinBox * spinBox = new QSpinBox(this);    //创建QSpinBox
    ui->mainToolBar->addWidget(spinBox);    //向工具栏添加QSpinBox部件
    //5.状态栏，设计器还不支持向状态栏中拖放部件，故用代码生成
    //显示临时信息，显示2000毫秒即2秒
    ui->statusBar->showMessage(tr("欢迎使用多文档编辑器"), 2000);
    //创建标签，设置标签样式并显示信息，然后让其以永久部件的形式添加到状态栏
    QLabel * permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText("www.qter.org");
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//中心部件
void MainWindow::on_action_New_triggered()
{
    //新建文本编辑器部件
    QTextEdit * edit = new QTextEdit(this);
    //使用QMdiArea类的addSubWindow()函数创建子窗口，以文本编辑器为中心部件
    QMdiSubWindow * child = ui->mdiArea->addSubWindow(edit);
    child->setWindowTitle(tr("多文档编辑器子窗口"));
    child->show();
}

//Dock部件
void MainWindow::on_action_Dock_triggered()
{
    ui->dockWidget_1->show();
}
