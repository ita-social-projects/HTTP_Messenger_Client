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
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/login", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface, RequestType::LOG_IN));
}

void RequestManager::signUp(QString login, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sign up");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/sign_up", jsonDocument);
    resultMap.emplace(reply,Requester(resultInterface, RequestType::SIGN_UP));
}

void RequestManager::updateLogin(QString token, QString newLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sendMessage");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUpdateLogin(token,newLogin);
    auto reply = post("/user/change_login", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATE_LOGIN));
}

void RequestManager::updatePassword(QString token, QString oldPassword, QString newPassword, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from updatePassword");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUpdatePassword(token,oldPassword,newPassword);
    auto reply = post("/user/change_password", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATE_PASSWORD));
}

void RequestManager::logOut(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getMessage");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/logout", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LOG_OUT));
}

void RequestManager::getChats(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getChats");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/get_chats", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GET_CHATS));
}

void RequestManager::getChatParticipants(QString token, unsigned long chatId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getChatParticipants");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToGetChatParticipants(token,chatId);
    auto reply = post("/chat/get_participants", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GET_CHAT_PARTICIPANTS));
}

void RequestManager::createChat(QString token, QString chatName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from createChat");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packChatInfo(token,chatName);
    auto reply = post("/chat/create_new", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::CREATE_CHAT));
}

void RequestManager::searchUser(QString token, QString searchingName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from searchUser");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToFindUsers(token,searchingName);
    auto reply = post("/user/find_users", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SEARCH_USER));
}

void RequestManager::addUserToChat(QString token, unsigned long chatId, QString memberLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from addUserToChat");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserToChat(token,chatId,memberLogin);
    auto reply = post("/chat/add_user", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::ADD_USER_TO_CHAT));
}

void RequestManager::leaveChat(QString token, unsigned long chatId, QString login, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from leaveChat");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserToChat(token,chatId,login);
    auto reply = post("/chat/leave", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LEAVE_CHAT));
}

void RequestManager::sendMessage(QString token, unsigned long chatId, QString message, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from sendMessage");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToSendMessage(token,message,chatId);
    auto reply = post("/messages/send", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SEND_MESSAGE));
}

void RequestManager::getMessages(QString token, unsigned long chatId, unsigned long lastMessageId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_ERROR("No result from getMessages");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToGetMessages(token,lastMessageId,chatId);
    auto reply = post("/messages/get", jsonDocument);
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GET_MESSAGES));
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
