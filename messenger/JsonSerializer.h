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
    QJsonDocument packToken(const QString& token);
    QJsonDocument packUpdateLogin(const QString& token,const QString& newLogin);
    QJsonDocument packUpdatePassword(const QString& token,const QString& oldPassword,const QString& newPassword);

    QJsonDocument packToFindUsers(const QString& token,const QString& searchString);
    QJsonDocument packToGetChatParticipants(const QString& token,const int chatId);
    QJsonDocument packToGetMessages(const QString& token,const int lastMsgId, const int chatId);
    QJsonDocument packToSendMessage(const QString& token, const QString& message,const int chatId);
    QJsonDocument packUserToChat(const QString& token, const int chatId, const QString& login);
    QJsonDocument packChatInfo(const QString& token, const QString& chatTitle);

};

#endif // JSONSERIALIZER_H
