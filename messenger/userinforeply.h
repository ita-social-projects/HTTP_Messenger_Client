#ifndef USERINFOREPLY_H
#define USERINFOREPLY_H
#include "JsonDeserializer.h"
#include "user.h"

class UserInfoReply: public JsonDeserializer<User*>
{
    QString login;

public:
    UserInfoReply();
    UserInfoReply(QString login);

    virtual User* extract(const QJsonDocument &replyInfo) override;
};

#endif // USERINFOREPLY_H
