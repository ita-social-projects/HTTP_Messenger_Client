#include "userinforeply.h"
#include "Logger.h"
UserInfoReply::UserInfoReply()
{

}

UserInfoReply::UserInfoReply(QString login)
{
    this->login = login;
}

User* UserInfoReply::extract(const QJsonDocument &replyInfo)
{
    User* user = User::getInstance();

    if(!replyInfo.isNull())
    {
       LOG_DEBUG("Setting access token");
        user->setAccessToken(replyInfo.object().value("token").toString());
    }

    return user;
}
