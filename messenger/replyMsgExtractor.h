#ifndef REPLYMSGEXTRACTOR_H
#define REPLYMSGEXTRACTOR_H

#include <QMainWindow>
#include "JsonDeserializer.h"

class ReplyMsgExtractor: public JsonDeserializer<QString>
{
public:
    ReplyMsgExtractor();
    QString extract(const QJsonDocument &replyInfo) override;
};

#endif // REPLYMSGEXTRACTOR_H
