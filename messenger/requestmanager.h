#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include <mutex>

#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QObject>

#include "JsonSerializer.h"

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
        virtual void OnRequestFinished(QNetworkReply *reply) = 0;
    };

private:
    RequestManager(QObject *parent = 0);

public:
    RequestManager(RequestManager &other) = delete;
    void operator=(const RequestManager &) = delete;
    static RequestManager *GetInstance();

    void login(QString username, QString password, RequestResultInterface *resultInterface);
    void signUp(QString username, QString password,RequestResultInterface *resultInterface);
private:
    QNetworkRequest createRequest(QString );
    QNetworkReply* post(QString, QJsonDocument&);
    QNetworkReply* get(QString);
    std::map<QNetworkReply *, RequestResultInterface *> resultMap;

public slots:
    void OnRequestResult(QNetworkReply *networkReply);
};

#endif // REQUESTMANAGER_H
