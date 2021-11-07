#include "jsondeserializer.h"
#include "Logger.h"
#include <QRegularExpression>

#define LOGIN "login"
#define TOKEN "token"

#define CHATS "chats"
#define CHAT_ID "id"
#define CHAT_TITLE "title"

#define TIMESTAMP "timestamp"
#define DATE 0
#define TIME 1

#define IMAGE "photo"
#define USERS "users"
#define MESSAGES "messages"
#define SENDER "sender"
#define CONTENT "content"
#define MESSAGE_ID "message_id"
#define ERROR_MESSAGE "what"

bool checkAllMessageFields(const QJsonObject& obj);
QPixmap pixmapFrom(const QJsonValue &val);

QVector<std::pair<QPixmap,QString>> JsonDeserializer::extractUsersInfo(const QJsonDocument &replyInfo)
{
    LOG_DEBUG("Extracting vector");
    QVector<std::pair<QPixmap,QString>> vect;
    QJsonObject jsonObject = replyInfo.object();

    if(replyInfo.toJson().contains(USERS))
    {
        QJsonArray jsonArray = jsonObject[USERS].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            if(obj.contains(LOGIN) )
            {
                QPixmap p = extractPhoto(replyInfo);
                if(p.isNull())
                {
                    p.load(":/icons/icons/profile.svg");
                }
                std::pair<QPixmap,QString> pair(p,obj[LOGIN].toString());
                vect.append(pair);
            }
        }
    }
    return vect;
}

std::map<unsigned long,QString> JsonDeserializer::extractChat(const QJsonDocument &replyInfo)
{
    LOG_DEBUG("Extracting chat");
    std::map<unsigned long,QString> map;
    QJsonObject jsonObject = replyInfo.object();
    if(jsonObject.contains(CHAT_ID) && jsonObject.contains(CHAT_TITLE))
    {
        map.emplace(jsonObject[CHAT_ID].toInt(),jsonObject[CHAT_TITLE].toString());
    }
    return map;
}

std::map<unsigned long,QString> JsonDeserializer::extractChats(const QJsonDocument &replyInfo)
{
    LOG_DEBUG("Extracting chats");
    std::map<unsigned long,QString> map;
    QJsonObject jsonObject = replyInfo.object();

    if(replyInfo.toJson().contains(CHATS))
    {
        QJsonArray jsonArray = jsonObject[CHATS].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            if(obj.contains(CHAT_ID) && obj.contains(CHAT_TITLE))
            {
                map.emplace(obj[CHAT_ID].toInt(),obj[CHAT_TITLE].toString());
            }
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
    LOG_DEBUG("Extracting user info");
    CurrentUser* user = CurrentUser::getInstance();

    if(!replyInfo.isNull() && replyInfo.toJson().contains(TOKEN))
    {
       user->setToken(replyInfo.object().value(TOKEN).toString());
    }

    if(replyInfo.toJson().contains(LOGIN))
    {
        user->setLogin(replyInfo.object().value(LOGIN).toString());
    }

    if(replyInfo.toJson().contains(IMAGE))
    {
        user->setImage(extractPhoto(replyInfo));
    }

    return user;
}

QVector<Message> JsonDeserializer::extractMessages(const QJsonDocument &replyInfo)
{
    LOG_DEBUG("Extracting messages");
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
                QStringList list = obj[TIMESTAMP].toString().split(QRegularExpression("\\s+"));
                Message msg(obj[MESSAGE_ID].toInt(),obj[SENDER].toString(),
                            obj[CONTENT].toString(),list.at(DATE), list.at(TIME));
                messages.append(msg);
            }
        }
    }
    return messages;
}

std::tuple<QPixmap, QVector<std::pair<QPixmap,QString>>> JsonDeserializer::extractChatInfo(const QJsonDocument &replyInfo)
{
    auto logins = extractUsersInfo(replyInfo);
    auto chatImg = extractPhoto(replyInfo);

    std::tuple res{chatImg,logins};
    return res;
}

QPixmap JsonDeserializer::extractPhoto(const QJsonDocument& replyInfo)
{
    LOG_DEBUG("Extracting messages");
    QJsonObject obj = replyInfo.object();
    QJsonValue val;

    if(obj.contains(IMAGE))
    {
        val = obj.value(IMAGE);
    }

    return pixmapFrom(val);
}

QPixmap pixmapFrom(const QJsonValue &val)
{
  auto const encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}

bool checkAllMessageFields(const QJsonObject& obj)
{
    if(obj.contains(MESSAGE_ID) &&
       obj.contains(SENDER) &&
       obj.contains(CONTENT) &&
       obj.contains(TIMESTAMP))
    {
        return true;
    }
    else
    {
        return false;
    }
}
