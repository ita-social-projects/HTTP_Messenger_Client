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
    /*QNetworkAccessManager *mgr = new QNetworkAccessManager();
        const QUrl url(QStringLiteral("http://google.com/api"));
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonObject obj;
        obj["login"] = "bel.vita";
        obj["password"] = "12345";
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();
        // or
        // QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}");
        QNetworkReply *reply = mgr->post(request, data);
        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());
                qDebug() << contents;
                qWarning("\n no error \n");
            }
            else{
                QString err = reply->errorString();
                qDebug() << err;
                qWarning("\n error: \n");
            }
            reply->deleteLater();
        });*/
    return true;
}
