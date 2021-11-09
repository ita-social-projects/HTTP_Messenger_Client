#include "currentchat.h"

#define DEFAULT_ID 0
#define DEFAULT_STR ""
#define DEFAULT_IMG QPixmap()

CurrentChat::CurrentChat()
{
    name = DEFAULT_STR;
    id = DEFAULT_ID;
    image = DEFAULT_IMG;
};

CurrentChat::CurrentChat(const CurrentChat& other)
{
    name = other.name;
    id = other.id;
    image = other.image;
    lastMessage = other.lastMessage;
}

void CurrentChat::resetChat(unsigned long id, QString name, QPixmap img)
{
    this->id = id;
    this->name = name;
    this->image = img;
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

void CurrentChat::setImage(QPixmap img)
{
    image = img;
}

void CurrentChat::closeChat()
{
    name = DEFAULT_STR;
    id = DEFAULT_ID;
    image = DEFAULT_IMG;
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

QPixmap CurrentChat::getImage()
{
    return image;
}
