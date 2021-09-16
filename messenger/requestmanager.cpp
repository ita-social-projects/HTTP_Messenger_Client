#include "requestmanager.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

QString server_url = "http://there_will_be_server_url"; // need changes

RequestManager::RequestManager()
{
    manager = new QNetworkAccessManager();
}

RequestManager::~RequestManager()
{
    delete manager;
}

QNetworkRequest RequestManager::createRequest(QString header)
{
    QNetworkRequest request;
    request.setUrl(QUrl(server_url + header));
    request.setHeader(QNetworkRequest::ContentTypeHeader, header);
    return request;
}

bool RequestManager::post(QString header, QJsonObject &json_data)
{
    QNetworkRequest request = createRequest(header);
    QNetworkReply *reply;
    QJsonDocument document(json_data);
    QByteArray postDataByteArray = document.toJson();
    reply = manager->post(request, postDataByteArray);
    bool serverAnswer;
    QObject::connect(reply, &QNetworkReply::finished, [reply, &serverAnswer]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
            serverAnswer = true;
        }
        else
        {
            QString err = reply->errorString();
            qDebug() << err;
            serverAnswer = false;
        }
        reply->deleteLater();
    });
    return serverAnswer;
}
