#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include <mutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include "JsonSerializer.h"

enum class RequestType
{
    LOG_IN,
    SIGN_UP,
    UPDATE_LOGIN,
    UPDATE_PASSWORD,
    LOG_OUT,
    SEARCH_USER,
    GET_CHATS,
    CREATE_CHAT,
    GET_CHAT_PARTICIPANTS,
    ADD_USER_TO_CHAT,
    LEAVE_CHAT,
    SEND_MESSAGE,
    GET_MESSAGES
};

class RequestManager : public QObject
{
    Q_OBJECT

private:
    static RequestManager *sharedInstance;
    static std::mutex mutex_;
    std::unique_ptr<QNetworkAccessManager> manager;
    const QString serverUrl = "http://localhost:8080/restdemo";

public:
    class RequestResultInterface
    {
    public:
        virtual void onRequestFinished(QNetworkReply *reply, RequestType type) = 0;
    };

private:
    RequestManager(QObject *parent = 0);

    class Requester
    {
        RequestResultInterface * interface;
        RequestType requestType;
    public:
        Requester() = default;
        Requester(RequestResultInterface * interface, RequestType type);
        RequestResultInterface * getInterface();
        RequestType getType();
    };

public:
    RequestManager(RequestManager &other) = delete;
    void operator=(const RequestManager &) = delete;
    static RequestManager *GetInstance();

    void login(QString login, QString password, RequestResultInterface *resultInterface);
    void signUp(QString login, QString password,RequestResultInterface *resultInterface);
    void updateLogin(QString token, QString newLogin, RequestResultInterface *resultInterface);
    void updatePassword(QString token, QString oldPassword, QString newPassword, RequestResultInterface *resultInterface);
    void logOut(QString token, RequestResultInterface *resultInterface);
    void getChats(QString token, RequestResultInterface *resultInterface);
    void getChatParticipants(QString token, unsigned long chatId, RequestResultInterface *resultInterface);
    void createChat(QString token, QString chatName, RequestResultInterface *resultInterface);
    void searchUser(QString token, QString searchingName, RequestResultInterface *resultInterface);
    void addUserToChat(QString token, unsigned long chatId, QString memberLogin, RequestResultInterface *resultInterface);
    void LeaveChat(QString token, unsigned long chatId, RequestResultInterface *resultInterface);
    void sendMessage(QString token, unsigned long chatId, QString massage, RequestResultInterface *resultInterface);
    void getMessages(QString tocken, unsigned long chatId, unsigned long lastMessageId, RequestResultInterface *resultInterface);
private:
    QNetworkRequest createRequest(QString );
    QNetworkReply* post(QString, QJsonDocument&);
    QNetworkReply* get(QString);

    std::map<QNetworkReply *, Requester> resultMap;

public slots:
    void OnRequestResult(QNetworkReply *networkReply);
};

#endif // REQUESTMANAGER_H
