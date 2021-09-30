#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include "requestmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    MainWindow(QString user_name);
    ~MainWindow();
    void checkNewMessages();

    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

private:
    bool CheckMessage();

signals:
    void ExitButtonClicked();

private slots:
    void on_UsersList_itemClicked(QListWidgetItem *item);
    void on_SendButton_clicked();
    void on_SearchUserButton_clicked();
    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

