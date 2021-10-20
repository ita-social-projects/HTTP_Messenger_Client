#include "chatinfo.h"
#include "ui_chatinfo.h"

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
    static bool mode = false;
    if(!mode)
    {
        ui->verticalWidget_FindUsers->show();
        ui->verticalWidget_Members->hide();
    }
    else
    {
        ui->verticalWidget_FindUsers->hide();
        ui->verticalWidget_Members->show();
    }
    mode = !mode;
}

void ChatInfo::on_pushButton_LeaveChat_clicked()
{
    //RequestManager::GetInstance()->leaveChat(CurrentUser::getInstance()->getToken(),CHAT-ID,userLogin);
}

void ChatInfo::on_pushButton_SearchUser_clicked()
{
    QString userLogin = ui->lineEdit_SearchUser->text();
    if(userLogin.isEmpty())
    {
        return;
    }
    //RequestManager::GetInstance()->searchUser(CurrentUser::getInstance()->getToken(),userLogin);
}

void ChatInfo::on_pushButton_Add_clicked()
{
    QString memberLogin = ui->label_MemberLogin->text();
    if(memberLogin.isEmpty())
    {
        return;
    }
    //RequestManager::GetInstance()->addUserToChar(CurrentUser::getInstance()->getToken(),CHAT-ID,memberLogin);
    ui->listWidget_Members->addItem(memberLogin);
}

void ChatInfo::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    if (reply->error())
    {
         QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
         return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    //if(type == RequestType::SEARCH_USER)
    //{
    //    QVector<QString> users = extractor.extractVector(document);
    //    ui->listWidget_Users->addItems(users);
    //}
    //else if(type == RequestType::ADD_USER_TO_CHAT)
    //{
    //    QString replyMsg = extractor.extractErrorMsg(document);
    //    ui->listWidget_Members->deleteItem(ui->label_MemberLogin->text());
    //    QMessageBox::information(nullptr,"Chat Information",replyMsg);
    //}
}

void ChatInfo::on_pushButton_Cancel_clicked()
{
    ui->label_MemberLogin->clear();
}
