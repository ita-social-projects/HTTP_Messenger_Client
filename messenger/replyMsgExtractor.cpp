#include "replyMsgExtractor.h"
#define STATUS "status"

ReplyMsgExtractor::ReplyMsgExtractor()
{

}

QString ReplyMsgExtractor::extract(const QJsonDocument &replyInfo)
{
    if(replyInfo.toJson().contains(STATUS))
    {
        return replyInfo.object().value(STATUS).toString();
    }
    return " ";
}

