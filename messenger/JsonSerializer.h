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
    QJsonDocument packUserInfo(const QString& pass,const QString& userLogin);
    QJsonDocument packMsg(const QString& sender,const QString& recLogin,const QString& msg);
};

#endif // JSONSERIALIZER_H
