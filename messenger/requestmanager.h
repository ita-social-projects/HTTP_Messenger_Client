#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>

class RequestManager
{
    std::unique_ptr<QNetworkAccessManager> manager;
public:
    RequestManager();
    QNetworkReply* post(QString, QJsonDocument&);
    QNetworkReply* get(QString);
private:
    QNetworkRequest createRequest(QString );
    bool waitForReply();
};

#endif // REQUESTMANAGER_H
