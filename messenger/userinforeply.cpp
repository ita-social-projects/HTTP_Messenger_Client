#include "userinforeply.h"

UserInfoReply::UserInfoReply()
{

}

UserInfoReply::UserInfoReply(QString login)
{
    this->login = login;
}

User UserInfoReply::extract(QJsonDocument &replyInfo)
{
    User user;
    user.setAccessToken("default");

    if(replyInfo.isNull())
    {
        return user;
    }

    user.setAccessToken(replyInfo.object().value("token").toString());

    return user;
}
