#ifndef SIGNUPINFO_H
#define SIGNUPINFO_H
#include <QMainWindow>
#include "ijsonSerializer.h"
#include "ijsondeserializer.h"

class SignUpInfo : public IJsonSerializer, public IJsonDeserializer
{
private:
    QString login;
    QString password;

public:
    SignUpInfo();

    QJsonObject& pack() override;
    void extract() override;
    bool send(QJsonObject &infoToSend) override;

    const QString GetLogin();
    const QString GetPassword();
    void SetLogin(const QString & str);
    void SetPassword(const QString & str);
};

#endif // SIGNUPINFO_H
