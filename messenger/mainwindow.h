#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include "requestmanager.h"
#include "currentchat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();
    void showMessage(QString from, QString message, QString date, QString time);
    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;
    void showChats();
    CurrentChat getCurrentChat();
private:
    CurrentChat currentChat;
    bool CheckMessage();
    bool notFirstLoad;
signals:
    void SignoutButtonClicked();
    void openProfileWindow();
    void openCreateChatWindow();
    void openChatInfo(CurrentChat);
public slots:
    void CheckNewMessages();

private slots:
    void on_ChatList_itemClicked(QListWidgetItem *item);
    void on_SendButton_clicked();
    void on_UserImg_clicked();
    void on_CreateChat_clicked();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionExit_triggered();
    void on_actionProfile_triggered();
    void on_actionSign_out_triggered();
    void on_ChatInfo_clicked();
    void on_SearchChat_textEdited(const QString &arg1);
    void addNewChat();
    void leaveChat();


private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H

