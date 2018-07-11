#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>

class QFile;

class QNetworkReply;
class QNetworkAccessManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager * manager;
    QNetworkReply * reply;
    QUrl url;
    QFile * file;

private slots:
    //获取网页信息
    //void replyFinished(QNetworkReply *);
    //下载文件
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64, qint64);

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
