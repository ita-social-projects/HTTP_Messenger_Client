#include "userInfoExtractor.h"

#define ID "id"
#define LOGIN "login"

UserInfoExtractor::UserInfoExtractor()
{

}

CurrentUser* UserInfoExtractor::extract(const QJsonDocument &replyInfo)
{
    CurrentUser* user = CurrentUser::getInstance();

    if(!replyInfo.isNull() && replyInfo.toJson().contains(ID))
    {
       user->setId(replyInfo.object().value(ID).toString());
    }

    if(replyInfo.toJson().contains(LOGIN))
    {
        user->setLogin(replyInfo.object().value(LOGIN).toString());
    }

    return user;
}
