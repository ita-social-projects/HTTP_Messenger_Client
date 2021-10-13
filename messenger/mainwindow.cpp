#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include "currentUser.h"
#include "profilewindow.h"

MainWindow::MainWindow(QString user_name)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchUser->setPlaceholderText(" Enter user to search:");

    QPixmap pixmap(":/icons/icons/profile.svg");
    QIcon ButtonIcon(pixmap);

     ui->UserImg->setIcon(ButtonIcon);
     ui->UserImg->setIconSize(ui->UserImg->size());

    RequestManager::GetInstance()->getChats(this);
    this->setWindowTitle("Toretto");
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
        CurrentUser *user = CurrentUser::getInstance();
        RequestManager::GetInstance()->sendMessage(user->getLogin(), ui->ChatName->text(), ui->EnterMessage->text(), this);

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

void MainWindow::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    if(type != RequestType::LOGIN && type != RequestType::SIGNUP)
    {
        if (reply->error())
        {
            QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
        }
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            if(type==RequestType::SENDMESSAGE)
            {
                // parsing json
                ui->Messages->addItem("Me: message");
            }
            if(type==RequestType::GETMESSAGE)
            {
                // parsing json
                ui->Messages->addItem("Somebody: message");
            }
            if(type==RequestType::GETCHATS)
            {
                // parsing json
                ui->UserList_2->addItem("ChatName");
            }
        }
    }
}

bool MainWindow::CheckMessage()
{
    if(ui->EnterMessage->text() == "" || ui->ChatName->text() == "")
    {
        return false;
    }
    return true;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(nullptr,"Project Team","Hello!\nWe are the team Lv.617-C++, and we are glad to see "
    "that you`re using our project messenger!\nGood luck and have fun!!!");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
     this->close();
}

void MainWindow::on_actionProfile_triggered()
{
    ProfileWindow *window = new ProfileWindow();
    window->setModal(true);
    window->show();
}

void MainWindow::on_UserImg_clicked()
{
    ProfileWindow *window = new ProfileWindow();
    window->setModal(true);
    window->show();
}
