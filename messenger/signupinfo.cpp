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

QJsonObject& SignUpInfo::pack()
{
    QFile file("Res.json");
    file.open(QIODevice::WriteOnly);
    QJsonObject json;

    json["login"] = login;
    json["password"] = password;

    file.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
    file.close();
}

void SignUpInfo::extract()
{
    QNetworkAccessManager * networkManager = new QNetworkAccessManager();
    // Connect networkManager response to the handler
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, &Sig));
    // We get the data, namely JSON file from a site on a particular url
    networkManager->get(QNetworkRequest(QUrl("https://hacker-news.firebaseio.com/v0/newstories.json")));

    QNetworkReply *reply;
    // If there are no errors
    if(!reply->error())
    {
        // So create an object Json Document, by reading into it all the data from the response
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

        // Taking from the document root object
        QJsonObject root = document.object();
        /* We find the object "departament", which is the very first in the root object.
         * Use the keys() method gets a list of all objects and the first index
         * Take away the name of the object on which we obtain its value
         * */
        ui->textEdit->append(root.keys().at(0) + ": " + root.value(root.keys().at(0)).toString());

        // The second value prescribe line
        QJsonValue jv = root.value("employees");
        // If the value is an array, ...
        if(jv.isArray()){
            // ... then pick from an array of properties
            QJsonArray ja = jv.toArray();
            // Going through all the elements of the array ...
            for(int i = 0; i < ja.count(); i++){
                QJsonObject subtree = ja.at(i).toObject();
                // Taking the values of the properties and last name by adding them to textEdit
                ui->textEdit->append(subtree.value("firstName").toString() +
                                     " " +
                                     subtree.value("lastName").toString());
            }
        }
        // At the end we take away the property of the number of employees of the department and also to output textEdit
           ui->textEdit->append(QString::number(root.value("number").toInt()));
     }
     reply->deleteLater();
}

bool SignUpInfo::send(QJsonObject &infoToSend)
{
    QNetworkRequest request(QUrl("http://example.com/exampleapi"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager netwManager;
    QNetworkReply *reply = netwManager.post(request, QJsonDocument(infoToSend).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    reply->deleteLater();

    /*
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    const QUrl url(QStringLiteral("http://google.com/api"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj;
    obj["login"] = "romusic";
    obj["password"] = "password";
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    // or
    // QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}");
    QNetworkReply *reply = mgr->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
             QString contents = QString::fromUtf8(reply->readAll());
             qDebug() << contents;
             qWarning("\n no error \n");
         }
         else
         {
              QString err = reply->errorString();
              qDebug() << err;
              qWarning("\n error: \n");
          }
          reply->deleteLater();
    });
    return true;
    */
}
