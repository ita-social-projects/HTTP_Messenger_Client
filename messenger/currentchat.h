#ifndef CURRENTCHAT_H
#define CURRENTCHAT_H
#include "message.h"
#include <vector>
#include <mutex>
#include <QPixmap>

class CurrentChat
{

public:
    CurrentChat();
    CurrentChat(const CurrentChat& other);

    void resetChat(unsigned long id, QString name, QPixmap img);
    void setLastMessage(Message message);
    void setName(QString name);
    void setImage(QPixmap img);
    void closeChat();

    unsigned long getId();
    QString getName();
    Message getLastMessage();
    QPixmap getImage();

private:
    QString name;
    unsigned long id;
    Message lastMessage;
    QPixmap image;
};

#endif // CURRENTCHAT_H
