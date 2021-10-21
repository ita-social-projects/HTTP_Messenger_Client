#include "JsonDeserializer.h"
#include "Logger.h"

#define LOGIN "login"

#define TOKEN "token"

#define CHATS "chats"
#define CHAT_ID "id"
#define CHAT_TITLE "title"

#define TIMESTAMP "timestamp"
#define DATE 0
#define TIME 1

#define USERS "users"
#define MESSAGES "messages"
#define SENDER "sender"
#define TEXT "text"
#define MESSAGE_ID "message_id"
#define ERROR_MESSAGE "what"

bool checkAllMessageFields(const QJsonObject& obj);

QVector<QString> JsonDeserializer::extractVector(const QJsonDocument &replyInfo)
{

    LOG_DEBUG("Extracting list of users");

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

std::map<unsigned long,QString> JsonDeserializer::extractChats(const QJsonDocument &replyInfo)
{

    LOG_DEBUG("Extracting list of chats");

    std::map<unsigned long,QString> map;
    QJsonObject jsonObject = replyInfo.object();

    if(replyInfo.toJson().contains(CHATS))
    {
        QJsonArray jsonArray = jsonObject[CHATS].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();

            map.insert(std::pair<int,QString>(obj[CHAT_ID].toString().toULong(),obj[CHAT_TITLE].toString()));
        }
    }
    return map;
}

QString JsonDeserializer::extractErrorMsg(const QJsonDocument &replyInfo)
{

    LOG_DEBUG("Extracting error message");

    if(replyInfo.toJson().contains(ERROR_MESSAGE))
    {
        return replyInfo.object().value(ERROR_MESSAGE).toString();
    }
    return " ";
}

CurrentUser* JsonDeserializer::extractUserInfo(const QJsonDocument &replyInfo)
{
    LOG_DEBUG("Extracting user`s info");
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

QVector<Message> JsonDeserializer::extractMessages(const QJsonDocument &replyInfo)
{

    LOG_DEBUG("Extracting list of messages");

    QVector<Message> messages;
    QJsonObject jsonObject = replyInfo.object();
    if(!jsonObject.empty() && jsonObject.contains(MESSAGES))
    {
        QJsonArray jsonArray = jsonObject[MESSAGES].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            if(checkAllMessageFields(obj))
            {
                QStringList list = obj[TIMESTAMP].toString().split("\\s");
                Message msg(obj[MESSAGE_ID].toInt(),obj[SENDER].toString(),
                            obj[TEXT].toString(),list.at(DATE),list.at(TIME));
                messages.append(msg);
            }
        }
    }
    return messages;
}

bool checkAllMessageFields(const QJsonObject& obj)
{
    if(obj.contains(MESSAGE_ID) &&
       obj.contains(SENDER) &&
       obj.contains(TEXT) &&
       obj.contains(TIMESTAMP))
    {
        return true;
    }
    else
    {
        return false;
    }
}
