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
    std::map<unsigned long,QString> extractMap(const QJsonDocument &replyInfo);
    QVector<QString> extractVector(const QJsonDocument &replyInfo);
    QString extractErrorMsg(const QJsonDocument &replyInfo);
    CurrentUser* extractUserInfo(const QJsonDocument &replyInfo);
};

#endif // JSONDESERIALIZER_H
