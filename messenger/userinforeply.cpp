#include "userinforeply.h"

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
       user->setAccessToken(replyInfo.object().value("token").toString());
    }

    return user;
}
