#include "currentchat.h"

#define DEFAULT_ID 0
#define DEFAULT_STR ""

CurrentChat* CurrentChat::instance{nullptr};
std::mutex CurrentChat::mtx;

CurrentChat* CurrentChat::getInstance()
{
    std::lock_guard<std::mutex> lock(mtx);
    if (instance == nullptr)
    {
        instance = new CurrentChat();
    }
    return instance;
}

CurrentChat::CurrentChat()
{
    name = DEFAULT_STR;
    id = DEFAULT_ID;
};

void CurrentChat::resetChat(unsigned long id, QString name)
{
    this->id = id;
    this->name = name;
    lastMessage.clear();
}

void CurrentChat::setLastMessage(Message message)
{
    this->lastMessage = message;
}

void CurrentChat::closeChat()
{
    name = DEFAULT_STR;
    id = DEFAULT_ID;
    lastMessage.clear();
}

unsigned long CurrentChat::getId()
{
    return id;
}

QString CurrentChat::getName()
{
    return name;
}

Message CurrentChat::getLastMessage()
{
    return lastMessage;
}

