#include "chatinfo.h"
#include "ui_chatinfo.h"

ChatInfo::ChatInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Information");
    ui->verticalWidget_FindUsers->hide();
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

}


void ChatInfo::on_pushButton_Add_clicked()
{

}

void ChatInfo::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    if (reply->error())
    {
         QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
    }
    else
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QString resReply = extractor.extractErrorMsg(document);
        QMessageBox::information(nullptr,"Profile",resReply);
    }
}
