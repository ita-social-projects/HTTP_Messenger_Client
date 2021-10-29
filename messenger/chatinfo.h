#ifndef CHATINFO_H
#define CHATINFO_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "requestmanager.h"
#include "jsondeserializer.h"
#include "currentchat.h"

namespace Ui {
class ChatInfo;
}

class ChatInfo : public QDialog, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit ChatInfo(CurrentChat chat);
    void onRequestFinished(QNetworkReply *reply, RequestType type) override;
    ~ChatInfo();

signals:
    void closing();
    void leaveChat();

private slots:
    void on_pushButton_AddMember_clicked();
    void on_pushButton_LeaveChat_clicked();
    void on_pushButton_Add_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_SearchUser_clicked();
    void closeEvent(QCloseEvent * e ) override;
    void on_listWidget_Users_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_EditChatName_clicked();
    void on_lineEdit_ChatName_editingFinished();

private:
    QValidator *validator;
    Ui::ChatInfo *ui;
    CurrentChat currentChat;
};

#endif
