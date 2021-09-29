#include "requestmanager.h"
#include <QEventLoop>
#include <QTimer>

QString serverUrl = "https://615376d53f4c430017159389.mockapi.io/api";

RequestManager::RequestManager() : manager(new QNetworkAccessManager())
{

}
QNetworkReply* RequestManager::post(QString header, QJsonDocument& jsonDocument)
{
    QNetworkRequest request = createRequest(header);
    QByteArray data = jsonDocument.toJson();
    QNetworkReply* reply = manager->post(request, data);
    if(waitForReply())
        return reply;
    return nullptr;
}
QNetworkReply* RequestManager::get(QString header)
{
    QNetworkRequest request = createRequest(header);
    QNetworkReply* reply = manager->get(request);
    if(waitForReply())
        return reply;
    return nullptr;
}
bool RequestManager::waitForReply()
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
        return true;
    }
    return false;
}
QNetworkRequest RequestManager::createRequest(QString header)
{
    QNetworkRequest request;
    request.setUrl(QUrl(serverUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, header);
    return request;
}
