#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>

class Message
{
    unsigned long id;
    QString writer;
    QString message;
    QString date;
    QString time;

public:
    Message();
    Message(unsigned long id, QString writer, QString message, QString date, QString time);

    void setId(unsigned long id);
    void setMessage(QString message);
    void setWriter(QString writer);
    void setDate(QString date);
    void setTime(QString time);

    void clear();

    unsigned long getId();
    QString getMessage();
    QString getWriter();
    QString getDate();
    QString getTime();

    void operator=(const Message& other);
};

#endif // MESSAGE_H
