#ifndef CURRENTUSER_H
#define CURRENTUSER_H
#include <QMainWindow>
#include <QMap>
#include <mutex>

class CurrentUser
{
public:
    CurrentUser(CurrentUser& other) = delete;
    void operator=(const CurrentUser& other) = delete;

    void setLogin(const QString& userLogin);
    void setId(const QString& userId);
    void setChats(const QMap<int,QString> chats);
    void setToken(const QString& token);

    const QMap<int,QString>& getChats();
    const QString& getLogin();
    const QString& getId();
    const QString& getToken();
    static CurrentUser* getInstance();

private:
    CurrentUser(){};
    CurrentUser(const QString& userLogin,const QString& userId)
        : login(userLogin), id(userId){}

    QString login;
    QString id;
    QString accessToken;
    QMap<int,QString> chats;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
