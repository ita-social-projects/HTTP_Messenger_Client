#ifndef REPLYMSGKEEPER_H
#define REPLYMSGKEEPER_H

#include <QMainWindow>
#include "JsonDeserializer.h"

class ReplyMsgKeeper: public JsonDeserializer<QString>
{
public:
    ReplyMsgKeeper();

    QString extract(QJsonDocument &replyInfo) override;
};

#endif // REPLYMSGKEEPER_H
