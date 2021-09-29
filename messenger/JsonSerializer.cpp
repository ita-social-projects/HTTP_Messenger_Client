#include "JsonSerializer.h"
#define LOGIN "login"
#define PASSWORD "password"

JsonSerializer::JsonSerializer()
{

}

QJsonDocument& JsonSerializer::pack(QString pass, QString userLogin)
{
    QJsonObject jsonInfo;

    // create test json file
    QFile file("Res.json");
    file.open(QIODevice::WriteOnly);

    jsonInfo[LOGIN] = userLogin;
    jsonInfo[PASSWORD] = pass;
    QJsonDocument document(jsonInfo);

    // write info in test json file
    file.write(QJsonDocument(jsonInfo).toJson(QJsonDocument::Indented));
    file.close();

    return document;
}
