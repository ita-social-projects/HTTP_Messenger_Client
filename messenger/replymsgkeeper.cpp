#include "replymsgkeeper.h"

ReplyMsgKeeper::ReplyMsgKeeper()
{

}

QString ReplyMsgKeeper::extract(const QJsonDocument &replyInfo)
{
    return replyInfo.object().value("status").toString();
}
