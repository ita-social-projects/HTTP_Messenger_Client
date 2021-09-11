#include <QApplication>
#include "windowmanager.h"
#include <curl/curl.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QMessageBox>

int main(int argc, char *argv[])
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
    QApplication a(argc, argv);
    WindowManager ui;
    return a.exec();
    return 0;
}
