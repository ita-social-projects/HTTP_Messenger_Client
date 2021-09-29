#include "JsonDeserializer.h"
#include <QDebug>


#define LOGIN "login"
#define SIGNUP "signUp"
#define PASSWORD "password"

JsonDeserializer::JsonDeserializer()
{

}

User JsonDeserializer::extract(QJsonDocument &replyInfo, QString header)
{
    if(header == LOGIN)
    {
        User user;
    }

    QJsonObject root = replyInfo.object();
    qDebug() << root.keys().at(0) + ": " + root.value(root.keys().at(0)).toString();

    QJsonValue jv = root.value("employees");
    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0; i < ja.count(); i++)
        {
            QJsonObject subtree = ja.at(i).toObject();
            // Taking the values of the properties and last name by adding them to textEdit
            qDebug() << subtree.value("firstName").toString() +
                                 " " +
                                 subtree.value("lastName").toString();
        }
    }
    // At the end we take away the property of the number of employees of the department and also to output textEdit
    qDebug() << QString::number(root.value("number").toInt());
}

