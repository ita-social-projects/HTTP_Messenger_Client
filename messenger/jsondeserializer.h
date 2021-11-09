#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QRegularExpression>
#include <QStringList>
#include <QString>

#include "currentuser.h"
#include "message.h"

class JsonDeserializer
{
public:
    QString extractErrorMsg(const QJsonDocument &replyInfo);
    std::map<unsigned long,std::pair<QPixmap,QString>> extractChats(const QJsonDocument &replyInfo);
    CurrentUser* extractUserInfo(const QJsonDocument &replyInfo);
    QVector<Message> extractMessages(const QJsonDocument &replyInfo);
    Message extractMessage(const QJsonDocument &replyInfo);
    std::tuple<QPixmap,  QVector<std::pair<QPixmap,QString>>> extractChatInfo(const QJsonDocument &replyInfo);
    QVector<std::pair<QPixmap,QString>> extractUsersInfo(const QJsonDocument &replyInfo);
    static QPixmap extractPhoto(const QJsonObject& replyInfo);
};

#endif // JSONDESERIALIZER_H
