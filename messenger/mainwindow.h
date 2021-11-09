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
    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

private:
    bool CheckMessage();
    void saveSystemMessage(QString message);
    void saveMessage(QString from, QString message, QString date, QString time);
    void showMessages();
    void showChats();
    void showSearchingMessage(int count, QString searchingMessage);
    QString setMessageProperties(QString message);

signals:
    void SignoutButtonClicked();
    void openProfileWindow();
    void openCreateChatWindow();
    void openChatInfo(CurrentChat);
    void openEmojiList();
    void finished();
    void start();

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
    void leaveChat();
    void updateLogin();
    void SetScrollBotButtonVisible();
    void on_ScrollBot_clicked();
    void closeEvent(QCloseEvent * e) override;
    void UpdateData();
    void on_emojiButton_clicked();
    void printEmoji(QString emoji);
    void update_ProfileImage();

private:
    Ui::MainWindow *ui;
    QScrollBar *ScrollBar;
    CurrentChat currentChat;
    std::vector<QListWidgetItem> conversation;
    std::vector<QListWidgetItem> chatList;
    int maxMessageLength;
};
#endif // MAINWINDOW_H

