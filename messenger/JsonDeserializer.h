#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

template <typename T>
class JsonDeserializer
{
public:
    virtual T extract(QJsonDocument &replyInfo) = 0;
};

#endif // JSONDESERIALIZER_H
