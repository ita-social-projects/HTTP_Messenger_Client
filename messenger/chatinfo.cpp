#include "chatinfo.h"
#include "ui_chatinfo.h"
#include "currentchat.h"

ChatInfo::ChatInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Information");
    ui->lineEdit_SearchUser->setPlaceholderText("Search user...");
    ui->verticalWidget_FindUsers->hide();

    QRegularExpression rx("[a-zA-Z0-9]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_SearchUser->setValidator(validator);
}
ChatInfo::~ChatInfo()
{
    delete ui;
}

void ChatInfo::on_pushButton_AddMember_clicked()
{
    if(ui->pushButton_AddMember->isChecked())
    {
        ui->verticalWidget_FindUsers->show();
        ui->verticalWidget_Members->hide();
    }
    else
    {
        ui->verticalWidget_FindUsers->hide();
        ui->verticalWidget_Members->show();
    }
}

void ChatInfo::on_pushButton_LeaveChat_clicked()
{
    CurrentUser* user = CurrentUser::getInstance();
    RequestManager::GetInstance()->leaveChat(user->getToken(), CurrentChat::getInstance()->getId(), user->getLogin(), this);
}

void ChatInfo::on_pushButton_SearchUser_clicked()
{
    QString userLogin = ui->lineEdit_SearchUser->text();
    if(userLogin.isEmpty())
    {
        return;
    }
    RequestManager::GetInstance()->searchUser(CurrentUser::getInstance()->getToken(), userLogin, this);
}

void ChatInfo::on_pushButton_Add_clicked()
{
    QString memberLogin = ui->label_MemberLogin->text();
    if(memberLogin.isEmpty())
    {
        return;
    }
    RequestManager::GetInstance()->addUserToChat(CurrentUser::getInstance()->getToken(), CurrentChat::getInstance()->getId(), memberLogin, this);
}

void ChatInfo::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (reply->error())
    {
        if(type == RequestType::ADD_USER_TO_CHAT)
        {
            ui->label_MemberLogin->clear();
        }
        QString replyMsg = extractor.extractErrorMsg(document);
        QMessageBox::critical(nullptr, "ERROR", replyMsg);
    }
    else
    {
        if(type == RequestType::SEARCH_USER)
        {
            QVector<QString> users = extractor.extractVector(document);
            ui->listWidget_Users->clear();
            ui->listWidget_Users->addItems(users);
        }
        if(type == RequestType::ADD_USER_TO_CHAT)
        {
            ui->listWidget_Members->addItem(ui->label_MemberLogin->text());
            ui->label_MemberLogin->clear();
        }
        if(type == RequestType::LEAVE_CHAT)
        {
            emit leaveChat();
            this->close();
        }
    }
}

void ChatInfo::on_pushButton_Cancel_clicked()
{
    ui->label_MemberLogin->clear();
}

void ChatInfo::closeEvent(QCloseEvent * e)
{
    emit closing();
}
