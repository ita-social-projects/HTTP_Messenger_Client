#include "createchat.h"
#include "ui_createchat.h"
#include <QMessageBox>

CreateChat::CreateChat() :
    QDialog(nullptr),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);
    this->setWindowTitle("Create Chat");
}

CreateChat::~CreateChat()
{
    delete ui;
}

void CreateChat::setUsers(const QVector<QString> users)
{
    this->users = users;
}

const QVector<QString>& CreateChat::getUsers()
{
    return this->users;
}

void CreateChat::on_pushButton_Cancel_clicked()
{
    this->close();
}

void CreateChat::closeEvent(QCloseEvent * e)
{
    emit closing();
}

void CreateChat::on_pushButton_Create_clicked()
{
    QString selectedMember;
    QString chatName = ui->lineEdit_ChatName->text();

    RequestManager::GetInstance()->createChat(CurrentUser::getInstance()->getToken(), chatName, this);
}

void CreateChat::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    if(type == RequestType::CREATE_CHAT)
    {
        JsonDeserializer extractor;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        if (reply->error())
        {
            QString resReply = extractor.extractErrorMsg(document);
            QMessageBox::critical(nullptr, "ERROR", resReply);
        }
        else
        {
            std::map<unsigned long, QString> map = extractor.extractChat(document);
            CurrentUser::getInstance()->addNewChat(map.begin()->first,map.begin()->second);
            emit addChat();
            this->close();
        }
    }
}
