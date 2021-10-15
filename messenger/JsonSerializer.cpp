#include "JsonSerializer.h"

#define LOGIN "login"
#define PASSWORD "pass"
#define NEW_PASSWORD "new_pass"
#define SENDER "sender"
#define RECEIVER "receiver"
#define MESSAGE "message"
#define USER_ID "id"

JsonSerializer::JsonSerializer()
{

}

QJsonDocument JsonSerializer::packUserInfo(const QString& pass,const QString& userLogin)
{
    QJsonObject jsonInfo;

    jsonInfo[LOGIN] = userLogin;
    jsonInfo[PASSWORD] = pass;

    QJsonDocument document(jsonInfo);
    return document;
}

QJsonDocument JsonSerializer::packMsg(const QString& userSender,const QString& userReceiverLogin,const QString& msg)
{
    QJsonObject jsonObject;

    jsonObject[SENDER] = userSender;
    jsonObject[RECEIVER] = userReceiverLogin;
    jsonObject[MESSAGE] = msg;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdateLogin(const QString& userID,const QString& newLogin)
{
    QJsonObject jsonObject;

    jsonObject[USER_ID] = userID;
    jsonObject[LOGIN] = newLogin;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdatePassword(const QString& userID,const QString& oldPassword,const QString& newPassword)
{
    QJsonObject jsonObject;

    jsonObject[USER_ID] = userID;
    jsonObject[PASSWORD] = oldPassword;
    jsonObject[NEW_PASSWORD] = newPassword;

    QJsonDocument doc(jsonObject);
    return doc;
}
