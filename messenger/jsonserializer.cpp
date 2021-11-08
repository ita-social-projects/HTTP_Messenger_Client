#include "jsonserializer.h"
#include "Logger.h"

#define NEW_PASSWORD "new_pass"
#define PASSWORD "pass"
#define LOGIN "login"
#define SEARCH_STRING "search_string"
#define LAST_MESSAGE_ID "last_message_id"
#define CHAT_ID "chat_id"
#define CHAT_TITLE "chat_title"

#define SENDER "sender"
#define RECEIVER "receiver"
#define MESSAGE "message"
#define TOKEN "token"

#define IMAGE "image"
QJsonValue jsonValFromPixmap(const QPixmap &p);

JsonSerializer::JsonSerializer()
{

}

QJsonDocument JsonSerializer::packUserInfo(const QString& pass,const QString& userLogin)
{
    LOG_DEBUG("Packing user info into json");
    QJsonObject jsonInfo;

    jsonInfo[LOGIN] = userLogin;
    jsonInfo[PASSWORD] = pass;

    QJsonDocument document(jsonInfo);
    return document;
}

QJsonDocument JsonSerializer::packToken(const QString& token)
{
    //LOG_DEBUG("Packing token into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdatedLogin(const QString& token,const QString& newLogin)
{
    LOG_DEBUG("Packing updated login into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[LOGIN] = newLogin;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdatedPassword(const QString& token,const QString& oldPassword,const QString& newPassword)
{
    LOG_DEBUG("Packing updated password into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[PASSWORD] = oldPassword;
    jsonObject[NEW_PASSWORD] = newPassword;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdateChatName(const QString& token,const int chatId,const QString& newName)
{
    LOG_DEBUG("Packing updated chat name into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_ID] = chatId;
    jsonObject[CHAT_TITLE] = newName;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToFindUsers(const QString& token,const QString& searchString)
{
    LOG_DEBUG("Packing list of needed users into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[SEARCH_STRING] = searchString;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToGetChatParticipants(const QString& token,const int chatId)
{
    LOG_DEBUG("Packing request for getting chat participants into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_ID] = chatId;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToGetMessages(const QString& token,const int lastMsgId, const int chatId)
{
    LOG_DEBUG("Packing request for getting messages into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[LAST_MESSAGE_ID] = lastMsgId;
    jsonObject[CHAT_ID] = chatId;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToSendMessage(const QString& token, const QString& message,const int chatId)
{
    LOG_DEBUG("Packing request for sending message into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[MESSAGE] = message;
    jsonObject[CHAT_ID] = chatId;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUserToChat(const QString& token, const int chatId, const QString& login)
{
    LOG_DEBUG("Packing request for change user state in chat into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_ID] = chatId;
    jsonObject[LOGIN] = login;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packChatInfo(const QString& token, const QString& chatTitle)
{
    LOG_DEBUG("Packing chat information into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_TITLE] = chatTitle;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packPhoto(const QPixmap& img)
{
    LOG_DEBUG("Packing photo into json");
    QJsonObject jsonObject;

    jsonObject[IMAGE] = jsonValFromPixmap(img);

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonValue jsonValFromPixmap(const QPixmap &p)
{
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG");
  auto const encoded = buffer.data().toBase64();
  return {QLatin1String(encoded)};
}
