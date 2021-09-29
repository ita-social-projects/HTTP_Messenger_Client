#include "user.h"

User::User()
{

}

void User::setLogin(QString userLogin)
{
    login = userLogin;
}

void User::setAccessToken(QString userAccessToken)
{
    accessToken = userAccessToken;
}

QString User::getLogin()
{
    return login;
}

QString User::getAccessToken()
{
    return accessToken;
}

void User::operator=(User& user)
{
    this->login = user.login;
    this->accessToken = user.accessToken;
}
