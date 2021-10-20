#include "JsonDeserializer.h"

#define LOGIN "Login"
#define TOKEN "token"
#define CHATS "chats"
#define CHAT_ID "id"
#define CHAT_TITLE "title"
#define USERS "users"
#define MESSAGE "what"

QVector<QString> JsonDeserializer::extractVector(const QJsonDocument &replyInfo)
{
    QVector<QString> vect;
    QJsonObject jsonObject = replyInfo.object();

    if(replyInfo.toJson().contains(USERS))
    {
        QJsonArray jsonArray = jsonObject[USERS].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            vect.append(obj[LOGIN].toString());
        }
    }
    return vect;
}

std::map<unsigned long,QString> JsonDeserializer::extractMap(const QJsonDocument &replyInfo)
{
    std::map<unsigned long,QString> map;
    QJsonObject jsonObject = replyInfo.object();

    if(replyInfo.toJson().contains(CHATS))
    {
        QJsonArray jsonArray = jsonObject[CHATS].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            map.insert(std::pair<int,QString>(obj[CHAT_ID].toInt(),obj[CHAT_TITLE].toString()));
        }
    }
    return map;
}

QString JsonDeserializer::extractErrorMsg(const QJsonDocument &replyInfo)
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

    if(!replyInfo.isNull() && replyInfo.toJson().contains(TOKEN))
    {
       user->setToken(replyInfo.object().value(TOKEN).toString());
    }

    if(replyInfo.toJson().contains(LOGIN))
    {
        user->setLogin(replyInfo.object().value(LOGIN).toString());
    }

    return user;
}
