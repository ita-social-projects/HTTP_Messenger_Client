#include "user.h"
User* User::instance{nullptr};
std::mutex User::mtx;

User* User::getInstance()
{
    std::lock_guard<std::mutex> lock(mtx);
    if(instance == nullptr)
    {
        instance = new User();
    }
    return instance;
}

void User::setLogin(const QString& userLogin)
{
    login = userLogin;
}

void User::setAccessToken(const QString& userAccessToken)
{
    accessToken = userAccessToken;
}

const QString& User::getLogin()
{
    return login;
}

const QString& User::getAccessToken()
{
    return accessToken;
}
