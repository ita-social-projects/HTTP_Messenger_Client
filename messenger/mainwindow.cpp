#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currentuser.h"
#include "profilewindow.h"
#include "createchat.h"
#include "Logger.h"
#include "cache.h"
#include "chatinfo.h"
#include <QMessageBox>
#include <QScrollBar>
MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RequestManager::GetInstance()->getChats(CurrentUser::getInstance()->getToken(), this);

    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchChat->setPlaceholderText(" Search chat...");
    ScrollBar = ui->Messages->verticalScrollBar();
    connect(ScrollBar, &QScrollBar::valueChanged, this, &MainWindow::SetScrollBotButtonVisible);
    this->setWindowTitle("Toretto");
    ui->UserName->setText(CurrentUser::getInstance()->getLogin());

//    ui->Messages->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents );
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
    currentChat.resetChat(chatId, item->text());
    ui->ChatInfo->setText(item->text());
    ui->Messages->clear();
    ui->EnterMessage->clear();

}

void MainWindow::on_SendButton_clicked()
{
    if(CheckMessage() && ui->ChatInfo->text() != "")
    {
        LOG_DEBUG("Send button clicked");
        CurrentUser *user = CurrentUser::getInstance();
        RequestManager::GetInstance()->sendMessage(user->getToken(), currentChat.getId(), ui->EnterMessage->text(), this);
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
    JsonDeserializer extractor;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (reply->error())
    {
        QString resReply = extractor.extractErrorMsg(document);
        LOG_ERROR(resReply.toStdString());
        QMessageBox::critical(nullptr, "ERROR", resReply);
    }
    else
    {
        if(type==RequestType::GET_CHATS)
        {
            std::map<unsigned long, QString> chats = extractor.extractChats(document);
            CurrentUser::getInstance()->setChats(chats);
            showChats();
        }
        else if(type==RequestType::GET_MESSAGES)
        {
            QVector<Message> msgs = extractor.extractMessages(document);
            if(msgs.isEmpty())
            {
                return;
            }
            for(auto msg: msgs)
            {
                if(msg.getWriter() == CurrentUser::getInstance()->getLogin())
                {
                    showMessage("Me:", msg.getMessage(), msg.getDate(), msg.getTime());
                }
                else
                {
                    showMessage(msg.getWriter(), msg.getMessage(), msg.getDate(), msg.getTime());
                }
                currentChat.setLastMessage(msgs[msgs.size() - 1]);

            }
            if (!notFirstLoad)
            {
                ui->Messages->scrollToBottom();
                notFirstLoad = true;
            }
            if (ScrollBar->value() == ScrollBar->maximum())
            {
                ui->Messages->scrollToBottom();
                ui->ScrollBot->setVisible(false);
            }
        }
        else if(type==RequestType::SEND_MESSAGE)
        {
            ui->EnterMessage->clear();
        }
        else if(type == RequestType::LOG_OUT)
        {
            emit SignoutButtonClicked();
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
    QString msgDate = currentChat.getLastMessage().getDate();
    if(msgDate != date)
    {
        QListWidgetItem* itemDate = new QListWidgetItem(date);
        itemDate->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        itemDate->setForeground(Qt::gray);
        ui->Messages->addItem(itemDate);
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
    ui->Messages->addItem(itemFrom);
    ui->Messages->addItem(itemMessage);
    ui->Messages->addItem(itemTime);
    ui->Messages->addItem("");
}

void MainWindow::on_actionSign_out_triggered()
{
    RequestManager::GetInstance()->logOut(CurrentUser::getInstance()->getToken(), this);
    Cache::DeleteFile();
}


void MainWindow::on_CreateChat_clicked()
{
    emit openCreateChatWindow();
}

void MainWindow::on_ChatInfo_clicked()
{
    if(ui->ChatInfo->text().isEmpty())
    {
        return;
    }
    emit openChatInfo(currentChat);
}

void MainWindow::addNewChat()
{
    showChats();
}

void MainWindow::leaveChat()
{
    CurrentUser::getInstance()->deleteChat(currentChat.getId());
    currentChat.closeChat();
    ui->ChatInfo->setText("");
    ui->Messages->clear();
    showChats();
}

void MainWindow::showChats()
{
    ui->ChatList->clear();
    std::map<unsigned long, QString> chats = CurrentUser::getInstance()->getChats();
    for(auto &a: chats)
    {
        ui->ChatList->addItem(a.second);
    }
}

void MainWindow::updateChatName(QString newName)
{
    CurrentUser::getInstance()->updateChat(currentChat.getId(), newName);
    currentChat.setName(newName);
    ui->ChatInfo->setText(newName);
    showChats();
}

void MainWindow::CheckNewMessages()
{
    RequestManager::GetInstance()->getMessages(CurrentUser::getInstance()->getToken(),
                                               currentChat.getId(),
                                               currentChat.getLastMessage().getId(),
                                               this);
}

CurrentChat MainWindow::getCurrentChat()
{
    return currentChat;
}

void MainWindow::on_ScrollBot_clicked()
{
     ui->Messages->scrollToBottom();
     ui->ScrollBot->setVisible(false);
}

void MainWindow::SetScrollBotButtonVisible()
{
    if (ScrollBar->value() != ScrollBar->maximum())
        ui->ScrollBot->setVisible(true);
    else
        ui->ScrollBot->setVisible(false);

}
