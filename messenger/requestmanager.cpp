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

const QUrl& RequestManager::getServerURL()
{
    return serverUrl;
}

void RequestManager::setServerURL(const QUrl& url)
{
    serverUrl = url;
}

void RequestManager::login(QString login, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {

        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/login", jsonDocument);
    LOG_DEBUG("Login request sended");
    resultMap.emplace(reply,Requester(resultInterface, RequestType::LOG_IN));
}

void RequestManager::signUp(QString login, QString password, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {

        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserInfo(password, login);
    auto reply = post("/user/sign_up", jsonDocument);
    LOG_DEBUG("Signup request sended");
    resultMap.emplace(reply,Requester(resultInterface, RequestType::SIGN_UP));
}

void RequestManager::checkToken(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {

        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/check_token", jsonDocument); // url???
    LOG_DEBUG("Check token request sended");
    resultMap.emplace(reply,Requester(resultInterface, RequestType::CHECK_TOKEN));
}

void RequestManager::updateLogin(QString token, QString newLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUpdatedLogin(token,newLogin);
    auto reply = post("/user/change_login", jsonDocument);
    LOG_DEBUG("Update login request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATE_LOGIN));
}

void RequestManager::updatePassword(QString token, QString oldPassword, QString newPassword, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUpdatedPassword(token,oldPassword,newPassword);
    auto reply = post("/user/change_password", jsonDocument);
    LOG_DEBUG("Update password request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATE_PASSWORD));
}

void RequestManager::deleteAccount(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/delete_account", jsonDocument); // url???
    LOG_DEBUG("Delete account sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::DELETE_ACCOUNT));
}


void RequestManager::logOut(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/logout", jsonDocument);
    LOG_DEBUG("Log out request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LOG_OUT));
}

void RequestManager::getChats(QString token, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToken(token);
    auto reply = post("/user/get_chats", jsonDocument);
    LOG_DEBUG("Get chats request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GET_CHATS));
}

void RequestManager::getChatParticipants(QString token, unsigned long chatId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToGetChatParticipants(token,chatId);
    auto reply = post("/chat/get_participants", jsonDocument);
    LOG_DEBUG("Get chat participants request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::GET_CHAT_PARTICIPANTS));
}

void RequestManager::createChat(QString token, QString chatName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packChatInfo(token,chatName);
    auto reply = post("/chat/create_new", jsonDocument);
    LOG_DEBUG("Create chat sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::CREATE_CHAT));
}

void RequestManager::updateChatName(QString token, unsigned long chatId, QString newName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUpdateChatName(token,chatId,newName);
    auto reply = post("/chat/update_title", jsonDocument); // url???
    LOG_DEBUG("Update chat name sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::UPDATE_CHAT_NAME));
}

void RequestManager::searchUser(QString token, QString searchingName, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToFindUsers(token,searchingName);
    auto reply = post("/user/find_users", jsonDocument);
    LOG_DEBUG("Search user request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SEARCH_USER));
}

void RequestManager::addUserToChat(QString token, unsigned long chatId, QString memberLogin, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserToChat(token,chatId,memberLogin);
    auto reply = post("/chat/add_user", jsonDocument);
    LOG_DEBUG("Add user request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::ADD_USER_TO_CHAT));
}

void RequestManager::leaveChat(QString token, unsigned long chatId, QString login, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packUserToChat(token,chatId,login);
    auto reply = post("/chat/leave", jsonDocument);
    LOG_DEBUG("Leave chat request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::LEAVE_CHAT));
}

void RequestManager::sendMessage(QString token, unsigned long chatId, QString message, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToSendMessage(token,message,chatId);
    auto reply = post("/messages/send", jsonDocument);
    LOG_DEBUG("Send message request sended");
    resultMap.emplace(reply, Requester(resultInterface, RequestType::SEND_MESSAGE));
}

void RequestManager::getMessages(QString token, unsigned long chatId, unsigned long lastMessageId, RequestResultInterface *resultInterface)
{
    if(resultInterface == nullptr)
    {
        LOG_DEBUG("Asnwer don't needed anymore");
        return;
    }
    JsonSerializer serializer;
    QJsonDocument jsonDocument = serializer.packToGetMessages(token,lastMessageId,chatId);
    auto reply = post("/messages/get", jsonDocument);
    LOG_DEBUG("Get messages request sended");
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
    request.setUrl(QUrl(serverUrl.toString() + header)); //
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
