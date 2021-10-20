#ifndef CURRENTUSER_H
#define CURRENTUSER_H
#include <QMainWindow>
#include <map>
#include <mutex>

class CurrentUser
{
public:
    CurrentUser(CurrentUser& other) = delete;
    void operator=(const CurrentUser& other) = delete;

    void setLogin(const QString& userLogin);
    void setChats(const QMap<int,QString> chats);
    void setToken(const QString& token);
    void setChats(const std::map<unsigned long, QString> chats);

    const QString& getLogin();
    const QString& getId();
    const QString& getToken();
    const std::map<unsigned long, QString>& getChats();
    static CurrentUser* getInstance();

    void addNewChat(unsigned long id, QString chatName);
    void deleteChat(unsigned long id);

private:
    CurrentUser(){};
    CurrentUser(const QString& userLogin, const QString& userToken)
        : login(userLogin), accessToken(userToken){}

    QString login;
    QString accessToken;
    std::map<unsigned long, QString> chats;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
