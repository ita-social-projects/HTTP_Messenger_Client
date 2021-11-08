#include "currentUser.h"

CurrentUser* CurrentUser::instance{nullptr};
std::mutex CurrentUser::mtx;

CurrentUser::CurrentUser()
{
    profileImg.load(":/icons/icons/profile.svg");
}

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

void CurrentUser::setChats(const std::map<unsigned long,std::pair<QPixmap,QString>> chats)
{
    this->chats = chats;
}

void CurrentUser::setImage(const QPixmap& image)
{
    this->profileImg = image;
}

void CurrentUser::clearChats()
{
    chats.clear();
}

const std::map<unsigned long,std::pair<QPixmap,QString>>& CurrentUser::getChats()
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

const QPixmap& CurrentUser::getImage()
{
    return profileImg;
}
