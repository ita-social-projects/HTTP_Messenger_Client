#include "requestmanager.h"
#include "Logger.h"
#include <QEventLoop>
#include <QTimer>

const QString serverUrl = "http://localhost:8080/restdemo";

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
        LOG_ERROR("No result from login");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password,username);
    auto reply = post("/user/login", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface, RequestType::LOGIN));
}

void RequestManager::signUp(QString username, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sign up");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password,username);
    auto reply = post("/user/sign_up", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface,RequestType::SIGNUP));
}

void RequestManager::sendMessage(QString from, QString to, QString message, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sendMessage");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packMsg(from,to,message);
    auto reply = post("/user/send_message", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SENDMESSAGE));
}

void RequestManager::getMessage(RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getMessage");
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
        LOG_ERROR("No result from getChats");
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
        LOG_ERROR("No result from OnResultRequest");
        return;
    }

    resultInterface->onRequestFinished(networkReply,type);
    networkReply->deleteLater();
}

QNetworkReply* RequestManager::post(QString header, QJsonDocument& jsonDocument)
{
    LOG_DEBUG("Post method sended");
    QNetworkRequest request = createRequest(header);
    QByteArray data = jsonDocument.toJson();
    return manager->post(request, data);
}

QNetworkReply* RequestManager::get(QString header)
{
    LOG_DEBUG("Get method sended");
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
