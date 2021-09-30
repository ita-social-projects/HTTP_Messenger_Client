#ifndef SIGNUPINFO_H
#define SIGNUPINFO_H
#include <QMainWindow>
#include "jsonparser.h"

class SignUpInfo : public JsonParser
{
private:
    QString login;
    QString password;

public:
    SignUpInfo();

    void pack() override;
    void unpack() override;
    bool send() override;

    const QString GetLogin();
    const QString GetPassword();
    void SetLogin(const QString & str);
    void SetPassword(const QString & str);
};

#endif // SIGNUPINFO_H
