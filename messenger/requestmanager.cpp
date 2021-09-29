#include "requestmanager.h"

#include <QJsonObject>

#include <QEventLoop>
#include <QTimer>

QString serverUrl = "https://615376d53f4c430017159389.mockapi.io/api";

RequestManager* RequestManager::sharedInstance{nullptr};
std::mutex RequestManager::mutex_;

RequestManager *RequestManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (sharedInstance == nullptr)
    {
        sharedInstance = new RequestManager();
    }
    return sharedInstance;
}

RequestManager::RequestManager(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager.get(), SIGNAL(finished(QNetworkReply*)), this, SLOT(OnRequestResult(QNetworkReply*)));
}

void RequestManager::login(QString username, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    QJsonObject jsonObj;
    jsonObj.insert("user",username);
    jsonObj.insert("password",password);
    QJsonDocument jsonDocument(jsonObj);
    auto reply = post("/login", jsonDocument);
    resultMap[reply] =  resultInterface;
}

void RequestManager::OnRequestResult(QNetworkReply *networkReply)
{
    RequestResultInterface *resultInterface = resultMap[networkReply];
    resultMap.erase(networkReply);
    if(resultInterface == nullptr)
    {
        // TODO: add log
        return;
    }

    resultInterface->OnRequestFinished(networkReply);
    networkReply->deleteLater();
}

QNetworkReply* RequestManager::post(QString header, QJsonDocument& jsonDocument)
{
    QNetworkRequest request = createRequest(header);
    QByteArray data = jsonDocument.toJson();
    return manager->post(request, data);
}

QNetworkReply* RequestManager::get(QString header)
{
    QNetworkRequest request = createRequest(header);
    return manager->get(request);
}

QNetworkRequest RequestManager::createRequest(QString header)
{
    QNetworkRequest request;
    request.setUrl(QUrl(serverUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, header);
    return request;
}
