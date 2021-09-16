#ifndef LOGININFO_H
#define LOGININFO_H
#include <QMainWindow>
#include "ijsonSerializer.h"
#include "ijsondeserializer.h"

class LoginInfo: public IJsonSerializer, public IJsonDeserializer
{
private:
    QString login;
    QString password;

public:
    LoginInfo();

    QJsonObject& pack() override;
    void extract() override;
    bool send(QJsonObject &infoToSend) override;

    const QString GetLogin();
    const QString GetPassword();
    void SetLogin(const QString & str);
    void SetPassword(const QString & str);
};

#endif // LOGININFO_H
