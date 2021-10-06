#ifndef USERINFOEXTRACTOR_H
#define USERINFOEXTRACTOR_H
#include "JsonDeserializer.h"
#include "user.h"

class UserInfoExtractor: public JsonDeserializer<CurrentUser*>
{
public:
    UserInfoExtractor();
    virtual CurrentUser* extract(const QJsonDocument &replyInfo) override;
};

#endif // USERINFOEXTRACTOR_H
