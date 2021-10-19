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
    token = userAccessToken;
}

const QString& CurrentUser::getLogin()
{
    return login;
}

const QString& CurrentUser::getToken()
{
    return token;
}
