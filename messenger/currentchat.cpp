#include "currentchat.h"

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

void CurrentChat::resetChat(unsigned long id, QString name)
{
    this->id = id;
    this->name = name;
    lastMessages.clear();
}

void CurrentChat::setLastMessage(Message message)
{
    this->lastMessages = message;
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
    return lastMessages;
}

