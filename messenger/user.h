#ifndef USER_H
#define USER_H
#include <QMainWindow>
#include <mutex>

class User
{
public:
    User(User& other) = delete;
    void operator=(const User& other) = delete;

    void setLogin(const QString& userLogin);
    void setAccessToken(const QString& userAccessToken);

    const QString& getLogin();
    const QString& getAccessToken();
    static User* getInstance();

private:
    User(){};
    User(const QString& userLogin,const QString& userAccessToken)
        : login(userLogin), accessToken(userAccessToken){}

    QString login;
    QString accessToken;

    static User* instance;
    static std::mutex mtx;
};

#endif // USER_H
