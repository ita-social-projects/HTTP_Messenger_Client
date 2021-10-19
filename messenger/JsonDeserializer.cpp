#include "JsonDeserializer.h"

#define ID "id"
#define LOGIN "Login"
#define MESSAGE "what"

QMap<int,QString> JsonDeserializer::extractMap(const QJsonDocument &replyInfo)
{
    QMap<int,QString> map;

    QVector<int> chatIDs;
    QVector<QString> chatTitles;

    QJsonObject jsonObject = replyInfo.object();
    QJsonArray jsonArray = jsonObject["chats"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        chatIDs.append(obj["id"].toInt());
        chatTitles.append(obj["title"].toString());
    }

    return map;
}

QString JsonDeserializer::extractMsg(const QJsonDocument &replyInfo)
{
    if(replyInfo.toJson().contains(MESSAGE))
    {
        return replyInfo.object().value(MESSAGE).toString();
    }
    return " ";
}

CurrentUser* JsonDeserializer::extractUserInfo(const QJsonDocument &replyInfo)
{
    CurrentUser* user = CurrentUser::getInstance();

    if(!replyInfo.isNull() && replyInfo.toJson().contains(ID))
    {
       user->setId(replyInfo.object().value(ID).toString());
    }

    if(replyInfo.toJson().contains(LOGIN))
    {
        user->setLogin(replyInfo.object().value(LOGIN).toString());
    }

    return user;
}
