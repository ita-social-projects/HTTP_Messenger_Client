#include "createchat.h"
#include "ui_createchat.h"
#include <QMessageBox>

CreateChat::CreateChat(MainWindow* mainPtr) :
    QDialog(nullptr),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);
    this->setWindowTitle("Create Chat");
    this->mainPtr = mainPtr;
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

void CreateChat::on_pushButton_Create_clicked()
{
    QString selectedMember;
    QString chatName = ui->lineEdit_ChatName->text();

    //RequestManager::GetInstance()->createChat(CurrentUser::getInstance()->getToken(), chatName, mainPtr);
    this->close();
}

void CreateChat::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    if (reply == nullptr)
    {
        QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
    }
    else
    {
        if (reply->error())
        {
             QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
        }
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            // повертають id чату і його title
            QString resReply = extractor.extractErrorMsg(document);
            QMessageBox::information(nullptr,"Profile",resReply);
        }
    }
}
