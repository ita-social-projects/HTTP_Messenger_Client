#ifndef USER_H
#define USER_H
#include <QMainWindow>

class User
{
public:
    User();

    void setLogin(QString userLogin);
    void setAccessToken(QString userAccessToken);

    QString getLogin();
    QString getAccessToken();

    void operator=(User& user);

private:
    QString login;
    QString accessToken;
};

#endif // USER_H
