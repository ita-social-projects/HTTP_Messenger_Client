#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currentUser.h"
#include "profilewindow.h"
#include "createchat.h"
#include "Logger.h"
#include "cache.h"
#include "chatinfo.h"
#include <QMessageBox>
#include "currentchat.h"

std::mutex MainWindow::mtx;

MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RequestManager::GetInstance()->getChats(CurrentUser::getInstance()->getToken(), this);

    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchChat->setPlaceholderText(" Search chat...");

    QPixmap pixmap(":/icons/icons/profile.svg");
    QIcon ButtonIcon(pixmap);

    ui->UserImg->setIcon(ButtonIcon);
    ui->UserImg->setIconSize(ui->UserImg->size());

    this->setWindowTitle("Toretto");
    ui->MessengerTitle->setText(this->windowTitle());
    ui->Messages->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ChatList_itemClicked(QListWidgetItem *item)
{
    int index = ui->ChatList->currentRow();
    auto iterator = CurrentUser::getInstance()->getChats().begin();
    for(int i = 0; i != index; i++)
    {
        ++iterator;
    }
    unsigned long chatId = iterator->first;
    CurrentChat::getInstance()->resetChat(chatId, item->text());
    ui->ChatInfo->setText(item->text());

    ui->Messages->clear();
    ui->EnterMessage->clear();
}

void MainWindow::on_SendButton_clicked()
{
    if(CheckMessage())
    {
        LOG_DEBUG("Send button clicked");
        CurrentUser *user = CurrentUser::getInstance();
        CurrentChat *chat = CurrentChat::getInstance();
        RequestManager::GetInstance()->sendMessage(user->getToken(), chat->getId(), ui->EnterMessage->text(), this);
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
        QString searchingString = ui->SearchChat->text();
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
        if(type==RequestType::GETMESSAGES)
        {
            // parsing json
            std::vector<Message> msgs;
            for(auto msg: msgs)
            {
                showMessage(msg.getWriter(), msg.getMessage(), msg.getDate(), msg.getTime());
            }
            CurrentChat::getInstance()->setLastMessage(msgs[msgs.size() - 1]);
        }
        if(type==RequestType::SENDMESSAGE)
        {
            // ???
            ui->EnterMessage->clear();
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
    emit openProfileWindow();
}

void MainWindow::on_UserImg_clicked()
{
    emit openProfileWindow();
}

void MainWindow::showMessage(QString from, QString message, QString date, QString time)
{
    if(CurrentChat::getInstance()->getLastMessage().getDate() != date)
    {
        QListWidgetItem* itemDate = new QListWidgetItem(date);
        itemDate->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        itemDate->setForeground(Qt::gray);
        mtx.lock();
        ui->Messages->addItem(itemDate);
        mtx.unlock();
    }
    QListWidgetItem* itemFrom = new QListWidgetItem(from);
    QListWidgetItem* itemMessage = new QListWidgetItem(message);
    QListWidgetItem* itemTime = new QListWidgetItem(time);
    itemTime->setForeground(Qt::gray);
    if(from == "Me:")
    {
        itemFrom->setForeground(Qt::red);
        itemFrom->setTextAlignment(Qt::AlignmentFlag::AlignRight);
        itemMessage->setTextAlignment(Qt::AlignmentFlag::AlignRight);
        itemTime->setTextAlignment(Qt::AlignmentFlag::AlignRight);
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
    RequestManager::GetInstance()->logOut(CurrentUser::getInstance()->getToken(), this);
    Cache::DeleteFile();
    emit SignoutButtonClicked();
}


void MainWindow::on_CreateChat_clicked()
{
    emit openCreateChatWindow(this);
}

void MainWindow::on_ChatInfo_clicked()
{
    ChatInfo *window = new ChatInfo();
    window->setModal(true);
    window->show();
}

void MainWindow::addNewChat()
{
    ui->ChatList->clear();
    std::map<unsigned long, QString> chats = CurrentUser::getInstance()->getChats();
    for(auto a: chats)
    {
        ui->ChatList->addItem(a.second);
    }
}

