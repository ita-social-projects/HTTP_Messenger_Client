#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QString user_name)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UserName->setText(user_name);

    ui->EnterMessage->setPlaceholderText(" Enter message:");
    ui->SearchUser->setPlaceholderText(" Enter user to search:");

    RequestManager::GetInstance()->getChats(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkNewMessages()
{
    while (true)
    {
        RequestManager::GetInstance()->getMessage(this);

//        QNetworkReply* answer = get("/new_message");
//        if (answer != nullptr)
//        {
//            if (!answer->error())
//            {
//                // show message
//            }
//            answer->deleteLater();
//        }
        QThread::sleep(1);
    }
}

void MainWindow::on_UsersList_itemClicked(QListWidgetItem *item)
{
    ui->Messages->clear();
    ui->EnterMessage->clear();
    ui->ChatName->setText(item->text());
}

void MainWindow::on_SendButton_clicked()
{
    if(CheckMessage())
    {
        RequestManager::GetInstance()->sendMessage(ui->UserName->text(), ui->ChatName->text(), ui->EnterMessage->text(), this);

    // get JsonDocument
//    QNetworkReply* answer = get("/send"); // post
//    if (answer == nullptr || answer->error())
//    {
//        // show "wasn't sended"
//    }
//    else
//    {
//        // show message
//        answer->deleteLater();
//    }
    }
}

void MainWindow::on_SearchUserButton_clicked()
{
    //RequestManager::GetInstance()->getChats(this);

    // get JsonDocument
//    QNetworkReply* answer = get("/search"); // post
//    if (answer == nullptr || answer->error())
//    {
//        // show "Not Found"
//    }
//    else
//    {
//        // show list
//        answer->deleteLater();
//    }
}

void MainWindow::on_ExitButton_clicked()
{
    emit ExitButtonClicked();
}

void MainWindow::OnRequestFinished(QNetworkReply *reply)
{

}

bool MainWindow::CheckMessage()
{
    if(ui->EnterMessage->text() == "" || ui->ChatName->text() == "")
    {
        return false;
    }
    return true;
}
