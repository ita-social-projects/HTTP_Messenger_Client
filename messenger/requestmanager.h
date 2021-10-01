#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include <mutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include "JsonSerializer.h"

enum class RequestType
{
    LOGIN,
    SIGNUP,
    SENDMESSAGE,
    GETMESSAGE,
    GETCHATS
};

class RequestManager : public QObject
{
    Q_OBJECT

private:
    static RequestManager *sharedInstance;
    static std::mutex mutex_;

    std::unique_ptr<QNetworkAccessManager> manager;
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

    void login(QString username, QString password, RequestResultInterface *resultInterface);
    void signUp(QString username, QString password,RequestResultInterface *resultInterface);
    void sendMessage(QString from, QString to, QString massage, RequestResultInterface *resultInterface);
    void getMessage(RequestResultInterface *resultInterface);
    void getChats(RequestResultInterface *resultInterface);
private:
    QNetworkRequest createRequest(QString );
    QNetworkReply* post(QString, QJsonDocument&);
    QNetworkReply* get(QString);
    std::map<QNetworkReply *, Requester> resultMap;

public slots:
    void OnRequestResult(QNetworkReply *networkReply);
};

#endif // REQUESTMANAGER_H
