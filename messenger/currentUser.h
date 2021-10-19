#ifndef CURRENTUSER_H
#define CURRENTUSER_H
#include <QMainWindow>
#include <mutex>

class CurrentUser
{
public:
    CurrentUser(CurrentUser& other) = delete;
    void operator=(const CurrentUser& other) = delete;

    void setLogin(const QString& userLogin);
    void setToken(const QString& userId);

    const QString& getLogin();
    const QString& getToken();
    static CurrentUser* getInstance();

private:
    CurrentUser(){};
    CurrentUser(const QString& userLogin,const QString& userToken)
        : login(userLogin), token(userToken){}

    QString login;
    QString token;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
