#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QRegularExpression>
#include <QStringList>
#include <QString>

#include "currentUser.h"
#include "message.h"

class JsonDeserializer
{
public:
    QString extractErrorMsg(const QJsonDocument &replyInfo);
    std::map<unsigned long,QString> extractChats(const QJsonDocument &replyInfo);
    CurrentUser* extractUserInfo(const QJsonDocument &replyInfo);
    QVector<QString> extractVector(const QJsonDocument &replyInfo);
    QVector<Message> extractMessages(const QJsonDocument &replyInfo);

};

#endif // JSONDESERIALIZER_H
