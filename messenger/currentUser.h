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
    void setId(const QString& userId);

    const QString& getLogin();
    const QString& getId();
    static CurrentUser* getInstance();

private:
    CurrentUser(){};
    CurrentUser(const QString& userLogin,const QString& userId)
        : login(userLogin), id(userId){}

    QString login;
    QString id;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
