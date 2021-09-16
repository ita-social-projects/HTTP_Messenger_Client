#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include <QtNetwork/QNetworkAccessManager>

class RequestManager
{
    QNetworkAccessManager *manager;

    QNetworkRequest createRequest(QString header);
public:
    RequestManager();
    ~RequestManager();
    bool post(QString header, QJsonObject &json_data);
};

#endif // REQUESTMANAGER_H
