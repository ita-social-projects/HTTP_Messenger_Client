#include "requestmanager.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>

QString serverUrl = "http://fcc-weather-api.glitch.me";

RequestManager::RequestManager():manager(new QNetworkAccessManager())
{

}
QString RequestManager::post(QString header, QJsonDocument& jsonData)
{
    QNetworkRequest request = createRequest(header);
    // ... //
    return "getReply(reply)";
}
QString RequestManager::get(QString header)
{
    QNetworkRequest request = createRequest(header);
    QNetworkReply* reply = manager->get(request);
    return getReply(reply);
}
QString RequestManager::getReply(QNetworkReply* reply) // return string reply
{
    QEventLoop loop;
    QTimer timer;

    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    QObject::connect(manager.release(), &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    timer.start(15000);
    loop.exec();
    if(timer.isActive())
    {
        if(reply->error())
        {
            return "ERROR";
        }
        else
        {
            // parsing
            return "SUCCESS";
        }
    }
    else
    {
        return "NO ANSWER";
    }
    reply->deleteLater();
}
QNetworkRequest RequestManager::createRequest(QString header)
{
    QNetworkRequest request;
    request.setUrl(QUrl(serverUrl + header));
    return request;
}
