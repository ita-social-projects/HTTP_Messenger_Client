#ifndef CHATINFO_H
#define CHATINFO_H

#include <QDialog>
#include <QMessageBox>
#include "requestmanager.h"
#include "JsonDeserializer.h"

namespace Ui {
class ChatInfo;
}

class ChatInfo : public QDialog, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = nullptr);
    void onRequestFinished(QNetworkReply *reply, RequestType type) override;
    ~ChatInfo();

private slots:
    void on_pushButton_AddMember_clicked();
    void on_pushButton_LeaveChat_clicked();
    void on_pushButton_Add_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_SearchUser_clicked();

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
