#include "signupinfo.h"

#include <iostream>
#include <QFile>


SignUpInfo::SignUpInfo()
{

}

const QString SignUpInfo::GetLogin()
{
    return  login;
}

const QString SignUpInfo::GetPassword()
{
    return password;
}

void SignUpInfo::SetLogin(const QString & str)
{
    this->login = str;
}

void SignUpInfo::SetPassword(const QString & str)
{
    this->password = str;
}

void SignUpInfo::pack()
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

void SignUpInfo::unpack()
{

}

bool SignUpInfo::send()
{
    return true;
}
