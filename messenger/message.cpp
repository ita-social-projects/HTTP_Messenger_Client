#include "message.h"

Message::Message()
{
    id = 0;
    writer = "";
    message = "";
    date = "";
    time = "";
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
    id = 0;
    writer = "";
    message = "";
    date = "";
    time = "";
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
}
