#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QNetworkAccessManager>

class RequestManager
{
    std::unique_ptr<QNetworkAccessManager> manager;
public:
    RequestManager();
    QString post(QString, QJsonDocument&);
    QString get(QString);
private:
    QNetworkRequest createRequest(QString );
    QString getReply(QNetworkReply*);
};

#endif // REQUESTMANAGER_H
