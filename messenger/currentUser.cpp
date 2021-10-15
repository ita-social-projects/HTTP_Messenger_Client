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

void CurrentUser::setId(const QString& userAccessToken)
{
    id = userAccessToken;
}

void CurrentUser::setChats(const QMap<int,QString> chats)
{
    this->chats = chats;
}

const QMap<int,QString>& CurrentUser::getChats()
{
    return chats;
}

const QString& CurrentUser::getLogin()
{
    return login;
}

const QString& CurrentUser::getId()
{
    return id;
}


