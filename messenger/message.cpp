#include "message.h"
#define DEFAULT_ID 0
#define DEFAULT_STR ""

Message::Message()
{
    id = DEFAULT_ID;
    writer = DEFAULT_STR;
    message = DEFAULT_STR;
    date = DEFAULT_STR;
    time = DEFAULT_STR;
}

Message::Message(unsigned long id,QString writer, QString message, QString date, QString time)
{
    this->id = id;
    this->writer = writer;
    this->message = message;
    this->date = date;
    this->time = time;
}

void Message::setId(unsigned long id)
{
    this->id = id;
}

void Message::setWriter(QString writer)
{
    this->writer = writer;
}

void Message::setMessage(QString message)
{
    this->message = message;
}

void Message::setDate(QString date)
{
    this->date = date;
}

void Message::setTime(QString time)
{
    this->time = time;
}

void Message::clear()
{
    id = DEFAULT_ID;
    writer = DEFAULT_STR;
    message = DEFAULT_STR;
    date = DEFAULT_STR;
    time = DEFAULT_STR;
}

unsigned long Message::getId()
{
    return id;
}

QString Message::getWriter()
{
    return writer;
}

QString Message::getMessage()
{
    return message;
}

QString Message::getDate()
{
    return date;
}

QString Message::getTime()
{
    return time;
}

void Message::operator=(const Message& other)
{
    id = other.id;
    message = other.message;
    date = other.date;
    time = other.time;
    writer = other.writer;
}
