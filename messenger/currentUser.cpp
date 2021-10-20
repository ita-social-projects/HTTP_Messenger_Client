#include "currentUser.h"

CurrentUser* CurrentUser::instance{nullptr};
std::mutex CurrentUser::mtx;

CurrentUser* CurrentUser::getInstance()
{
    std::lock_guard<std::mutex> lock(mtx);
    if(instance == nullptr)
    {
        instance = new CurrentUser();
    }
    return instance;
}

void CurrentUser::setLogin(const QString& userLogin)
{
    login = userLogin;
}

void CurrentUser::setToken(const QString& userAccessToken)
{
    accessToken = userAccessToken;
}

void CurrentUser::setChats(const std::map<unsigned long, QString> chats)
{
    this->chats = chats;
}

const std::map<unsigned long, QString>& CurrentUser::getChats()
{
    return chats;
}

const QString& CurrentUser::getLogin()
{
    return login;
}

const QString& CurrentUser::getToken()
{
    return accessToken;
}

 void CurrentUser::addNewChat(unsigned long id, QString chatName)
 {
     chats.emplace(id, chatName);
 }
