#include "logininfo.h"
#include <QFile>

LoginInfo::LoginInfo()
{

}

void LoginInfo::pack()
{
    QFile file("Res.json");
    file.open(QIODevice::WriteOnly);
    QJsonObject json;

    json["login"] = login;

    QString hashedPassword;
    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Sha1);
    hash->addData(password.toUtf8());
    hashedPassword = hash->result();

    json["password"] = hashedPassword;

    file.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
    file.close();
}

void LoginInfo::unpack()
{

}

bool LoginInfo::send()
{
    return true;
}
