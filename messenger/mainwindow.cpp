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
bool checkEqualityOfChats(const std::map<unsigned long,std::pair<QPixmap,QString>>&,const std::map<unsigned long,std::pair<QPixmap,QString>>&);

MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->EnterMessage->setPlaceholderText(" Send a message...");
    ui->SearchChat->setPlaceholderText(" Search chat...");
    ScrollBar = ui->Messages->verticalScrollBar();
    connect(ScrollBar, &QScrollBar::valueChanged, this, &MainWindow::SetScrollBotButtonVisible);
    this->setWindowTitle("Toretto");
    ui->EnterMessage->setHidden(true);
    ui->SendButton->setHidden(true);
    ui->ScrollBot->setHidden(true);
    ui->emojiButton->setHidden(true);
    ui->EnterMessage->setMaxLength(255);
    ui->UserImg->setIcon(CurrentUser::getInstance()->getImage());
    maxMessageLength = 0;
    ui->UserName->setText(CurrentUser::getInstance()->getLogin());
    RequestManager::GetInstance()->checkToken(CurrentUser::getInstance()->getToken(), this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ChatList_itemClicked(QListWidgetItem *item)
{
    maxMessageLength = ui->Messages->width() / 6.5 / 2 - 3;
    conversation.clear();
    int index = ui->ChatList->currentRow();
    auto iterator = CurrentUser::getInstance()->getChats().begin();
    for(int i = 0; i != index; i++)
    {
        ++iterator;
    }
    unsigned long chatId = iterator->first;
    currentChat.resetChat(chatId, item->text(), iterator->second.first);
    ui->ChatInfo->setText(item->text());
    ui->Messages->clear();
    ui->EnterMessage->clear();
    ui->EnterMessage->setHidden(false);
    ui->SendButton->setHidden(false);
    ui->emojiButton->setHidden(false);
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
    showSearchingMessage(activedElements, searchingString);
}

void MainWindow::showSearchingMessage(int count, QString searchingMessage)
{
    if(searchingMessage != "")
    {
        if(count == 0)
        {
            ui->FoundMessage->setText("Not Found");
        }
        else
        {
            std::string message = "Founded " + std::to_string(count) + " chats: ";
            ui->FoundMessage->setText(message.c_str());
        }
    }
    else
    {
        ui->FoundMessage->setText("All chats:");
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
        if(type==RequestType::GET_CHATS || type==RequestType::GET_MESSAGES)
        {
            emit finished();
        }
        QMessageBox::critical(nullptr, "ERROR", resReply);
        if(type == RequestType::CHECK_TOKEN)
        {
            Cache::DeleteCacheFile();
            emit SignoutButtonClicked();
        }
    }
    else
    {
        if(type==RequestType::GET_CHATS)
        {
            auto chatsInfo = extractor.extractChats(document);
            bool isEqual = checkEqualityOfChats(CurrentUser::getInstance()->getChats(),chatsInfo);
            if(!isEqual)
            {
                chatList.clear();
                ui->ChatList->clear();
                CurrentUser::getInstance()->setChats(chatsInfo);
                showChats();
                if(currentChat.getId() != 0)
                {
                    ui->ChatInfo->setText(chatsInfo[currentChat.getId()].second);
                    currentChat.setName(chatsInfo[currentChat.getId()].second);
                    currentChat.setImage(chatsInfo[currentChat.getId()].first);
                }
            }

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
                    showMessage("Me:", msg.getMessage(), msg.getDate(), msg.getTime().split('.')[0]);
                }
                else
                {
                    showMessage(msg.getWriter() + ':', msg.getMessage(), msg.getDate(), msg.getTime().split('.')[0]);
                }
                currentChat.setLastMessage(msg);
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
            Cache::DeleteCacheFile();
            emit SignoutButtonClicked();
        }
        else if(type == RequestType::CHECK_TOKEN)
        {
            emit start();
        }
    }
}

bool checkEqualityOfChats(const std::map<unsigned long,std::pair<QPixmap,QString>>& chat1,const std::map<unsigned long,std::pair<QPixmap,QString>>& chat2)
{
    if(chat1.size() != chat2.size())
    {
        return false;
    }
    for(auto &it: chat1)
    {
        if(it.second.first.toImage() != chat2.at(it.first).first.toImage() ||
           it.second.second != chat2.at(it.first).second)
        {
            return false;
        }
    }
    return true;
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
    if(currentChat.getLastMessage().getDate() != date)
    {
        QListWidgetItem itemDate(date);
        itemDate.setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        itemDate.setForeground(Qt::gray);
        conversation.push_back(itemDate);
        ui->Messages->addItem(&conversation.back());
    }
    QListWidgetItem itemFrom(from);
    QListWidgetItem itemMessage(setMessageProperties(message));
    QListWidgetItem itemTime(time);
    itemTime.setForeground(Qt::gray);
    if(from == "Me:")
    {
        itemFrom.setForeground(Qt::red);
        itemFrom.setTextAlignment(Qt::AlignmentFlag::AlignRight);
        itemMessage.setTextAlignment(Qt::AlignmentFlag::AlignRight);
        itemTime.setTextAlignment(Qt::AlignmentFlag::AlignRight);
    }
    else
    {
        itemFrom.setForeground(Qt::blue);
    }
    conversation.push_back(itemFrom);
    ui->Messages->addItem(&conversation.back());
    conversation.push_back(itemMessage);
    ui->Messages->addItem(&conversation.back());
    conversation.push_back(itemTime);
    ui->Messages->addItem(&conversation.back());
    ui->Messages->addItem("");
}

QString MainWindow::setMessageProperties(QString message)
{
    auto words = message.split(' ');
    QString resultString = "";
    int currentLength = 0;
    for(auto &word : words)
    {
        if(currentLength + word.length() > maxMessageLength)
        {
           resultString += '\n';
           currentLength = 0;
        }
        else
        {
            resultString += ' ';
            currentLength += 1;
        }
        resultString += word;
        currentLength += word.length();
    }
    return resultString;
}

void MainWindow::on_actionSign_out_triggered()
{
    RequestManager::GetInstance()->logOut(CurrentUser::getInstance()->getToken(), this);
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

void MainWindow::leaveChat()
{
    conversation.clear();
    currentChat.closeChat();
    ui->ChatInfo->setText("");
    ui->Messages->clear();
    ui->EnterMessage->setHidden(true);
    ui->SendButton->setHidden(true);
    ui->ScrollBot->setHidden(true);
    ui->emojiButton->setHidden(true);
}

void MainWindow::showChats()
{
    auto chats = CurrentUser::getInstance()->getChats();
    for(auto &a: chats)
    {
        QListWidgetItem chat(a.second.second);
        chat.setIcon(a.second.first);
        chatList.push_back(chat);
    }
    for(auto &a: chatList)
    {
        ui->ChatList->addItem(&a);
    }
}

void MainWindow::UpdateData()
{
    if (currentChat.getId() != 0)
    {
        RequestManager::GetInstance()->getMessages(CurrentUser::getInstance()->getToken(),
                                                   currentChat.getId(),
                                                   currentChat.getLastMessage().getId(),
                                                   this);
    }
    RequestManager::GetInstance()->getChats(CurrentUser::getInstance()->getToken(), this);
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

void MainWindow::closeEvent(QCloseEvent * e)
{
    conversation.clear();
    CurrentUser::getInstance()->clearChats();
    CurrentUser::getInstance()->setImage(QPixmap());
    emit finished();
}

void MainWindow::updateLogin()
{
    ui->UserName->setText(CurrentUser::getInstance()->getLogin());
}

void MainWindow::on_emojiButton_clicked()
{
    emit openEmojiList();
}

void MainWindow::printEmoji(QString emoji)
{
    ui->EnterMessage->insert(emoji);
}

void MainWindow::update_ProfileImage()
{
    ui->UserImg->setIcon(CurrentUser::getInstance()->getImage());
}
