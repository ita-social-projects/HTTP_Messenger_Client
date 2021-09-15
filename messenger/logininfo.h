#ifndef LOGININFO_H
#define LOGININFO_H
#include <QMainWindow>
#include "jsonparser.h"

class LoginInfo: public JsonParser
{
private:
    QString login;
    QString password;

public:
    LoginInfo();

    void pack() override;
    void unpack() override;
    bool send() override;

    const QString GetLogin();
    const QString GetPassword();
    void SetLogin(const QString & str);
    void SetPassword(const QString & str);
};

#endif // LOGININFO_H
