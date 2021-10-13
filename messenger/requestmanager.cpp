#include "requestmanager.h"
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
        // TODO: add log.
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
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password,username);
    auto reply = post("/user/sign_up", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface,RequestType::SIGNUP));
}

void RequestManager::sendMessage(QString userID, QString chatID, QString message, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packMsg(userID,chatID,message);
    auto reply = post("/user/send_message", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SENDMESSAGE));
}

void RequestManager::getMessage(QString userID, QString chatID, RequestResultInterface *resultInterface)
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

void RequestManager::getChats(QString userID, RequestResultInterface *resultInterface)
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

void RequestManager::createChat(QString userID, QString chatName, QVector<QString> members, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/create_chat", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::CREATECHATS));
}

void RequestManager::searchUser(QString userID, QString searchingName, RequestResultInterface *resultInterface)
{

}

void RequestManager::updateLogin(QString userID, QString newLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/update_login", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATELOGIN));
}

void RequestManager::updatePassword(QString userID, QString newPassword, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/update_password", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATEPASSWORD));
}

void RequestManager::signOut(QString userID, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/signout", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SIGNOUT));
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

    resultInterface->onRequestFinished(networkReply,type);
    networkReply->deleteLater();
}

QNetworkReply* RequestManager::post(QString header, QJsonDocument& jsonDocument)
{
    QNetworkRequest request = createRequest(header);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
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
    request.setUrl(QUrl(serverUrl + header));
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
