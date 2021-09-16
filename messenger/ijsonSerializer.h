#ifndef IJSONSERIALIZER_H
#define IJSONSERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class IJsonSerializer
{
public:
    IJsonSerializer();

    virtual QJsonObject& pack() = 0;
    virtual bool send(QJsonObject &infoToSend) = 0;
};

#endif // IJSONSERIALIZER_H
