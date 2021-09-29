#include "replymsgkeeper.h"

ReplyMsgKeeper::ReplyMsgKeeper()
{

}

QString ReplyMsgKeeper::extract(QJsonDocument &replyInfo)
{
    return replyInfo.object().value("status").toString();
}
