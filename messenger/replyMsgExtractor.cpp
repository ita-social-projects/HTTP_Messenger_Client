#include "replyMsgExtractor.h"
#define STATUS "status"
#define MESSAGE "what"

ReplyMsgExtractor::ReplyMsgExtractor()
{

}

QString ReplyMsgExtractor::extract(const QJsonDocument &replyInfo)
{
    if(replyInfo.toJson().contains(STATUS))
    {
        return replyInfo.object().value(STATUS).toString();
    }
    if(replyInfo.toJson().contains(MESSAGE))
    {
        return replyInfo.object().value(MESSAGE).toString();
    }
    return " ";
}
