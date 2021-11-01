#ifndef CURRENTCHAT_H
#define CURRENTCHAT_H
#include "message.h"
#include <vector>
#include <mutex>

class CurrentChat
{

public:
    CurrentChat();
    CurrentChat(const CurrentChat& other);

    void resetChat(unsigned long id, QString name);
    void setLastMessage(Message message);
    void setName(QString name);
    void closeChat();

    unsigned long getId();
    QString getName();
    Message getLastMessage();

private:
    QString name;
    unsigned long id;
    Message lastMessage;
};

#endif // CURRENTCHAT_H
