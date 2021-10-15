#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currentUser.h"
#include "profilewindow.h"
#include "Logger.h"
#include <QMessageBox>
#include <QThread>
#include <QFont>

std::mutex MainWindow::mtx;

MainWindow::MainWindow(QString user_name)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchChat->setPlaceholderText(" Enter user to search:");

    QPixmap pixmap(":/icons/icons/profile.svg");
    QIcon ButtonIcon(pixmap);

     ui->UserImg->setIcon(ButtonIcon);
     ui->UserImg->setIconSize(ui->UserImg->size());

    RequestManager::GetInstance()->getChats(this);
    this->setWindowTitle("Toretto");
    ui->Messages->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkNewMessages()
{
    LOG_DEBUG("Checking new messages");
    while (true)
    {
        RequestManager::GetInstance()->getMessage(this);
        QThread::sleep(1);
    }
}

void MainWindow::on_ChatList_itemClicked(QListWidgetItem *item)
{
    int index = ui->ChatList->currentRow();
    auto iterator = CurrentUser::getInstance()->getChats().begin();
    for(int i = 0; i != index; i++)
    {
        ++iterator;
    }
    unsigned long chatID = iterator->first;
    CurrentUser::getInstance()->setCurrentChat(chatID);
    ui->ChatName->setText(item->text());

    ui->Messages->clear();
    ui->EnterMessage->clear();
    //RequestManager::GetInstance()->getCorrespondence(CurrentUser::getInstance()->getId(), chatID, this);
}

void MainWindow::on_SendButton_clicked()
{
    if(CheckMessage())
    {
        LOG_DEBUG("Send button clicked");
        CurrentUser *user = CurrentUser::getInstance();
        RequestManager::GetInstance()->sendMessage(user->getLogin(), ui->ChatName->text(), ui->EnterMessage->text(), this);
        //showMessage("Me:", ui->EnterMessage->text());
        //ui->EnterMessage->clear();
    }
}

void MainWindow::on_SearchChat_textEdited(const QString &arg)
{
    QListWidgetItem* item = nullptr;
    if(arg == "")
    {
        for(int i = 0; i <ui->ChatList->count(); i++)
        {
            item = ui->ChatList->item(i);
            if(item->isHidden())
            {
                item->setHidden(false);
            }
        }
    }
    else
    {
        QString searchingString = ui->SearchChat->text();
        for(int i = 0; i <ui->ChatList->count(); i++)
        {
            item = ui->ChatList->item(i);
            if(!item->text().contains(searchingString))
            {
                item->setHidden(true);
            }
            else
            {
                item->setHidden(false);
            }
        }
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
        if(type==RequestType::GETMESSAGE)
        {
            // parsing json
            showMessage("Bro:", "Bro's message for me");
        }
        if(type==RequestType::GETCHATS)
        {
            // parsing json
            std::map<unsigned long, QString> chats;
            CurrentUser::getInstance()->setChats(chats);
            for(auto a: chats)
            {
                ui->ChatList->addItem(a.second);
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
    LOG_DEBUG("About project button clicked");
    QMessageBox::about(nullptr,"Project Team","Hello!\nWe are the team Lv.617-C++, and we are glad to see "
    "that you`re using our project messenger!\nGood luck and have fun!!!");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    LOG_DEBUG("About QT button clicked");
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
    mtx.lock();
    ui->Messages->addItem(itemFrom);
    ui->Messages->addItem(itemMessage);
    ui->Messages->addItem("");
    mtx.unlock();
}

