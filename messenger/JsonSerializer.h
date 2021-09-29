#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class JsonSerializer
{
public:
    JsonSerializer();
    QJsonDocument pack(QString pass, QString userLogin);
};

#endif // JSONSERIALIZER_H
