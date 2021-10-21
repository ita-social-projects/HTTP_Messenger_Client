#include "JsonSerializer.h"
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

QJsonDocument JsonSerializer::packMsg(const QString& userSender,const QString& userReceiverLogin,const QString& msg)
{
    LOG_DEBUG("Packing message into json");
    QJsonObject jsonObject;

    jsonObject[SENDER] = userSender;
    jsonObject[RECEIVER] = userReceiverLogin;
    jsonObject[MESSAGE] = msg;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToken(const QString& token)
{
    LOG_DEBUG("Packing token into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdateLogin(const QString& token,const QString& newLogin)
{
    LOG_DEBUG("Packing updated login into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[LOGIN] = newLogin;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUpdatePassword(const QString& token,const QString& oldPassword,const QString& newPassword)
{
    LOG_DEBUG("Packing updated password into json");
    QJsonObject jsonObject;

    jsonObject[TOKEN] = token;
    jsonObject[PASSWORD] = oldPassword;
    jsonObject[NEW_PASSWORD] = newPassword;

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

QJsonDocument JsonSerializer::packToGetChatParticipants(const QString& token,const unsigned long chatId)
{
    LOG_DEBUG("Packing request for getting chat participants into json");
    QJsonObject jsonObject;
    QString chatIdStr = QString::number(chatId);

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_ID] = chatIdStr;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToGetMessages(const QString& token,const unsigned long lastMsgId, const unsigned long chatId)
{
    LOG_DEBUG("Packing request for getting messages into json");
    QJsonObject jsonObject;

    QString chatIdStr = QString::number(chatId);
    QString lastMsgIdStr = QString::number(lastMsgId);

    jsonObject[TOKEN] = token;
    jsonObject[LAST_MESSAGE_ID] = lastMsgIdStr;
    jsonObject[CHAT_ID] = chatIdStr;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packToSendMessage(const QString& token, const QString& message,const unsigned long chatId)
{
    LOG_DEBUG("Packing request for sending message into json");
    QJsonObject jsonObject;
    QString chatIdStr = QString::number(chatId);

    jsonObject[TOKEN] = token;
    jsonObject[MESSAGE] = message;
    jsonObject[CHAT_ID] = chatIdStr;

    QJsonDocument doc(jsonObject);
    return doc;
}

QJsonDocument JsonSerializer::packUserToChat(const QString& token, const unsigned long chatId, const QString& login)
{
    LOG_DEBUG("Packing request for change user state in chat into json");
    QJsonObject jsonObject;
    QString chatIdStr = QString::number(chatId);

    jsonObject[TOKEN] = token;
    jsonObject[CHAT_ID] = chatIdStr;
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
