#include "chatinfo.h"
#include "ui_chatinfo.h"

ChatInfo::ChatInfo(CurrentChat chat) :
    QDialog(nullptr),
    ui(new Ui::ChatInfo),
    currentChat(chat)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Information");
    ui->lineEdit_SearchUser->setPlaceholderText("Search user...");

    QRegularExpression rx("[a-zA-Z0-9]+");
    validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_SearchUser->setValidator(validator);
    ui->verticalWidget_FindUsers->hide();

    ui->lineEdit_ChatName->setText(currentChat.getName());
    ui->lineEdit_ChatName->setReadOnly(true);
    ui->lineEdit_ChatName->blockSignals(true);

    RequestManager::GetInstance()->getChatParticipants(CurrentUser::getInstance()->getToken(), currentChat.getId(), this);
}

ChatInfo::~ChatInfo()
{
    delete validator;
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
    auto reply = QMessageBox::question(nullptr, "ChatInfo", "If you leave this chat then you can't come back until "
                                                           "another member of this chat adds you again. "
                                                           "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        CurrentUser* user = CurrentUser::getInstance();
        RequestManager::GetInstance()->leaveChat(user->getToken(), currentChat.getId(), user->getLogin(), this);
    }
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
    RequestManager::GetInstance()->addUserToChat(CurrentUser::getInstance()->getToken(), currentChat.getId(), memberLogin, this);
}

void ChatInfo::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (reply->error())
    {
        QString replyMsg = extractor.extractErrorMsg(document);
        QMessageBox::critical(nullptr, "ERROR", replyMsg);
        if(type == RequestType::ADD_USER_TO_CHAT)
        {
            ui->label_MemberLogin->clear();
        }
    }
    else
    {
        if(type == RequestType::SEARCH_USER)
        {
            QVector<QString> users = extractor.extractUsersLogin(document);
            ui->listWidget_Users->clear();
            ui->listWidget_Users->addItems(users);
        }
        else if(type == RequestType::ADD_USER_TO_CHAT)
        {
            ui->listWidget_Members->addItem(ui->label_MemberLogin->text());
            ui->label_MemberLogin->clear();
        }
        else if(type == RequestType::LEAVE_CHAT)
        {
            emit leaveChat();
            this->close();
        }
        else if(type == RequestType::GET_CHAT_PARTICIPANTS)
        {
            QVector<QString> users = extractor.extractUsersLogin(document);
            ui->listWidget_Members->addItems(users);
        }
    }
}

void ChatInfo::on_pushButton_Cancel_clicked()
{
    ui->label_MemberLogin->clear();
}

void ChatInfo::closeEvent(QCloseEvent * e )
{
    emit closing();
}

void ChatInfo::on_listWidget_Users_itemDoubleClicked(QListWidgetItem *item)
{
    QString user = ui->listWidget_Users->currentItem()->text();
    ui->label_MemberLogin->setText(user);
}

void ChatInfo::on_pushButton_EditChatName_clicked()
{
    ui->lineEdit_ChatName->blockSignals(false);
    ui->lineEdit_ChatName->setReadOnly(false);
    ui->lineEdit_ChatName->setFocus();
}

void ChatInfo::on_lineEdit_ChatName_editingFinished()
{
    RequestManager::GetInstance()->updateChatName(CurrentUser::getInstance()->getToken(), currentChat.getId(), ui->lineEdit_ChatName->text(), this);
}
