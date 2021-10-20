#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QDialog>
#include <QVector>
#include "mainwindow.h"
#include "requestmanager.h"
#include "JsonDeserializer.h"

namespace Ui {
class CreateChat;
}

class CreateChat : public QDialog, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit CreateChat(MainWindow* mainPtr);
    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

    void setUsers(const QVector<QString> users);
    const QVector<QString>& getUsers();

    ~CreateChat();

private slots:
    void on_pushButton_Cancel_clicked();
    void on_pushButton_Create_clicked();

private:
    QVector<QString> users;
    Ui::CreateChat *ui;
    MainWindow *mainPtr;
};

#endif // CREATECHAT_H
