#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "user.h"

class JsonDeserializer
{
public:
    JsonDeserializer();
    User extract(QJsonDocument &replyInfo, QString header);
};

#endif // JSONDESERIALIZER_H
