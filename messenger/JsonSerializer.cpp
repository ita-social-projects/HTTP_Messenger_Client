#include "JsonSerializer.h"
#include "Logger.h"
#define LOGIN "login"
#define PASSWORD "password"
#define SENDER "sender"
#define RECEIVER "receiver"
#define MESSAGE "message"


JsonSerializer::JsonSerializer()
{

}

QJsonDocument JsonSerializer::packUserInfo(const QString& pass,const QString& userLogin)
{
    LOG_DEBUG("Packing user info into json");
    QJsonObject jsonInfo;

    // create test json file
    QFile file("Res.json");
    file.open(QIODevice::WriteOnly);

    jsonInfo[LOGIN] = userLogin;
    jsonInfo[PASSWORD] = pass;
    QJsonDocument document(jsonInfo);

    // write info in test json file
    file.write(QJsonDocument(jsonInfo).toJson(QJsonDocument::Indented));
    file.close();

    return document;
}

QJsonDocument JsonSerializer::packMsg(const QString& userSenderToken,const QString& userReceiverLogin,const QString& msg)
{
    LOG_DEBUG("Packing message into json");
    QJsonObject jsonObject;

    jsonObject[SENDER] = userSenderToken;
    jsonObject[RECEIVER] = userReceiverLogin;
    jsonObject[MESSAGE] = msg;

    QJsonDocument doc(jsonObject);
    return doc;
}
