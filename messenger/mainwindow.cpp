#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currentUser.h"
#include "profilewindow.h"
#include "createchat.h"
#include "Logger.h"
//#include "cache.h"
#include "chatinfo.h"
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
    ui->SearchUser->setPlaceholderText(" Search chat...");

    RequestManager::GetInstance()->getChats(this);
    this->setWindowTitle("Toretto");
    ui->MessengerTitle->setText(this->windowTitle());
    ui->Messages->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents );
    ui->SendButton->setShortcut(Qt::Key_Return);
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
    ui->ChatInfo->setText(item->text());

    ui->Messages->clear();
    ui->EnterMessage->clear();
    ui->ChatInfo->setText(item->text());
    //RequestManager::GetInstance()->getCorrespondence(CurrentUser::getInstance()->getId(), chatID, this);
}

void MainWindow::on_SendButton_clicked()
{
    if(CheckMessage())
    {
        LOG_DEBUG("Send button clicked");
        CurrentUser *user = CurrentUser::getInstance();
        RequestManager::GetInstance()->sendMessage(user->getLogin(), ui->ChatInfo->text(), ui->EnterMessage->text(), this);
        //showMessage("Me:", ui->EnterMessage->text(), "00:00:00");
        //ui->EnterMessage->clear();
    }
}

void MainWindow::on_SearchChat_textEdited(const QString &arg)
{
    ui->FoundMessage->clear();
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
        ui->FoundMessage->setText("All chats:");
    }
    else
    {
        QString searchingString = ui->SearchUser->text();
        int activedElements = 0;
        for(int i = 0; i < ui->ChatList->count(); i++)
        {
            item = ui->ChatList->item(i);
            if(!item->text().contains(searchingString))
            {
                item->setHidden(true);
            }
            else
            {
                activedElements++;
                item->setHidden(false);
            }
        }
        if(activedElements == 0)
        {
            ui->FoundMessage->setText("Not Found");
        }
        else
        {
            std::string message = "Founded " + std::to_string(activedElements) + " chats: ";
            ui->FoundMessage->setText(message.c_str());
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
            showMessage("Me:", ui->EnterMessage->text(), "00:00:00");
            ui->EnterMessage->clear();
        }
        if(type==RequestType::GETMESSAGE)
        {
            // parsing json
            showMessage("Bro:", "Bro's message for me", "00:00:00");
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
    if(ui->EnterMessage->text() == "" || ui->ChatInfo->text() == "")
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

void MainWindow::showMessage(QString from, QString message, QString time)
{
    QListWidgetItem* itemFrom = new QListWidgetItem(from);
    QListWidgetItem* itemMessage = new QListWidgetItem(message);
    QListWidgetItem* itemTime = new QListWidgetItem(time);
    itemTime->setForeground(Qt::gray);
    if(from == "Me:")
    {
        itemFrom->setForeground(Qt::red);
        itemFrom->setTextAlignment(0x0002);
        itemMessage->setTextAlignment(0x0002);
        itemTime->setTextAlignment(0x0002);
    }
    else
    {
        itemFrom->setForeground(Qt::blue);
    }
    mtx.lock();
    ui->Messages->addItem(itemFrom);
    ui->Messages->addItem(itemMessage);
    ui->Messages->addItem(itemTime);
    ui->Messages->addItem("");
    mtx.unlock();
}

void MainWindow::on_actionSign_out_triggered()
{
    //RequestManager::GetInstance()->signOut(CurrentUser::getInstance()->getId());
    // Cache::DeleteFile();
    emit SignoutButtonClicked();
}


void MainWindow::on_CreateChat_clicked()
{
    CreateChat *window = new CreateChat(this);
    window->setModal(true);
    window->show();
}

void MainWindow::on_ChatInfo_clicked()
{
    ChatInfo *window = new ChatInfo();
    window->setModal(true);
    window->show();
}

