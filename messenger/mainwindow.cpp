#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QFont>
#include "currentUser.h"
#include <mutex>

MainWindow::MainWindow(QString user_name)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchUser->setPlaceholderText(" Enter user to search:");

    RequestManager::GetInstance()->getChats(CurrentUser::getInstance()->getToken(), this);
    this->setWindowTitle("Toretto");
    ui->Messages->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents );
}

MainWindow::~MainWindow()
{
    delete ui;
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
        //RequestManager::GetInstance()->sendMessage(user->getLogin(), ui->ChatName->text(), ui->EnterMessage->text(), this);
        //showMessage("Me:", ui->EnterMessage->text());
        //ui->EnterMessage->clear();
    }
}

void MainWindow::onRequestFinished(QNetworkReply *reply, RequestType type)
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
            showMessage("Me:", ui->EnterMessage->text());
            ui->EnterMessage->clear();
        }
        if(type==RequestType::GETMESSAGES)
        {
            // parsing json
            showMessage("Bro:", "Bro's message for me");
        }
        if(type==RequestType::GETCHATS)
        {
            // parsing json
            ui->UserList_2->addItem("ChatName");
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
     emit ExitButtonClicked();
}

std::mutex mutex_;
void MainWindow::showMessage(QString from, QString message)
{
    QListWidgetItem* itemFrom = new QListWidgetItem(from);
    QListWidgetItem* itemMessage = new QListWidgetItem(message);

    if(from == "Me:")
    {
        itemFrom->setForeground(Qt::red);
        itemFrom->setTextAlignment(0x0002);
        itemMessage->setTextAlignment(0x0002);
    }
    else
    {
        itemFrom->setForeground(Qt::blue);
    }
    mutex_.lock();
    ui->Messages->addItem(itemFrom);
    ui->Messages->addItem(itemMessage);
    ui->Messages->addItem("");
    mutex_.unlock();
}
