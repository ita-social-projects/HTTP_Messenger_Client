#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QCryptographicHash>

class JsonParser
{
public:
    JsonParser();

    virtual void pack() = 0;
    virtual void unpack() = 0;
    virtual bool send() = 0;
};

#endif // JSONPARSER_H
