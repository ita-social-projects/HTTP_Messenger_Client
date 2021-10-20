#ifndef CURRENTCHAT_H
#define CURRENTCHAT_H
#include "message.h"
#include <vector>
#include <mutex>

class CurrentChat
{

public:
    CurrentChat(CurrentChat& other) = delete;
    void operator=(const CurrentChat& other) = delete;
    static CurrentChat* getInstance();

    void resetChat(unsigned long id, QString name);
    void setLastMessage(Message message);

    unsigned long getId();
    QString getName();
    Message getLastMessage();

private:
    CurrentChat(){};

    QString name;
    unsigned long id;
    Message lastMessages;

    static CurrentChat* instance;
    static std::mutex mtx;
};

#endif // CURRENTCHAT_H
