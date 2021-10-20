#include "requestmanager.h"
#include "Logger.h"

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

void RequestManager::login(QString login, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from login");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/login", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface, RequestType::LOGIN));
}

void RequestManager::signUp(QString login, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sign up");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/sign_up", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface, RequestType::SIGNUP));
}

void RequestManager::updateLogin(QString tocken, QString newLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sendMessage");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/update_login", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATELOGIN));
}

void RequestManager::updatePassword(QString tocken, QString oldPassword, QString newPassword, RequestResultInterface *resultInterface)
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

void RequestManager::logOut(QString tocken, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getMessage");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/log_out", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LOGOUT));
}

void RequestManager::getChats(QString tocken, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getChats");
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/get_chats", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GETCHATS));
}

void RequestManager::getChatParticipants(QString token, unsigned long chatId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/get_chat_participants", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GETCHATPARTICIPANTS));
}

void RequestManager::createChat(QString tocken, QString chatName, RequestResultInterface *resultInterface)
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
    resultMap.emplace(reply, Requester(resultInterface, RequestType::CREATECHAT));
}

void RequestManager::searchUser(QString tocken, QString searchingName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/search_user", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SEARCHUSER));
}

void RequestManager::addUserToChat(QString token, unsigned long chatId, QString memberLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/add_user_to_chat", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::ADDUSERTOCHAT));
}

void RequestManager::LeaveChat(QString token, unsigned long chatId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument; // parsing
    auto reply = post("/user/leave_chat", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LEAVECHAT));
}

void RequestManager::sendMessage(QString token, unsigned long chatId, QString massage, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument;
    auto reply = post("/user/send_message", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SENDMESSAGE));
}

void RequestManager::getMessages(QString tocken, unsigned long chatId, unsigned long lastMessageId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        // TODO: add log.
        // DO nothing if result will not be used
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument;
    auto reply = post("/user/get_messages", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GETMESSAGES));
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
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
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
