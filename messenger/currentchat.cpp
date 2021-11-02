#include "currentchat.h"

#define DEFAULT_ID 0
#define DEFAULT_STR ""

CurrentChat::CurrentChat()
{
    name = DEFAULT_STR;
    id = DEFAULT_ID;
};

CurrentChat::CurrentChat(const CurrentChat& other)
{
    name = other.name;
    id = other.id;
    lastMessage = other.lastMessage;
}

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

void CurrentChat::setName(QString name)
{
    this->name = name;
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

