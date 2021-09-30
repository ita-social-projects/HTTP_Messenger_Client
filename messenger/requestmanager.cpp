#include "requestmanager.h"

#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>

QString serverUrl = "http://server_url";

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
    // Roman json
    QJsonObject jsonObj;
    jsonObj.insert("user",username);
    jsonObj.insert("password",password);
    QJsonDocument jsonDocument(jsonObj);

    auto reply = post("/user/login", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LOGIN));
}

void RequestManager::signup(QString username, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    // Roman json
    QJsonObject jsonObj;
    jsonObj.insert("user",username);
    jsonObj.insert("password",password);
    QJsonDocument jsonDocument(jsonObj);

    auto reply = post("/user/register", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SIGNUP));
}

void RequestManager::sendMessage(QString from, QString to, QString message, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    // Roman json
    QJsonObject jsonObj;
    jsonObj.insert("from", from);
    jsonObj.insert("to",to);
    jsonObj.insert("message", message);
    QJsonDocument jsonDocument(jsonObj);

    auto reply = post("/user/send_message", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SENDMESSAGE));
}

void RequestManager::getMessage(RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    auto reply = get("/user/get_message");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GETMESSAGE));
}

void RequestManager::getChats(RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    auto reply = get("/user/get_chats");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GETCHATS));
}

void RequestManager::OnRequestResult(QNetworkReply *networkReply)
{
    RequestResultInterface *resultInterface = resultMap[networkReply].getInterface();
    RequestType type = resultMap[networkReply].getType();
    resultMap.erase(networkReply);
    if(resultInterface == nullptr)
    {
        // TODO: add log
        return;
    }
    resultInterface->OnRequestFinished(networkReply, type);
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

RequestManager::Requester::Requester(RequestResultInterface * interface, RequestType type)
{
    this->interface = interface;
    this->requestType = type;
}

RequestManager::RequestResultInterface * RequestManager::Requester::getInterface()
{
    return interface;
}

RequestType RequestManager::Requester::getType()
{
    return requestType;
}
