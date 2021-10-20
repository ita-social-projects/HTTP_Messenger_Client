#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "currentUser.h"

class JsonDeserializer
{
public:
    QMap<int,QString> extractMap(const QJsonDocument &replyInfo);
    QString extractMsg(const QJsonDocument &replyInfo);
    CurrentUser* extractUserInfo(const QJsonDocument &replyInfo);
};

#endif // JSONDESERIALIZER_H
