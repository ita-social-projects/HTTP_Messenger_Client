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
    void setChats(const std::map<unsigned long,std::pair<QPixmap,QString>> chats);
    void setImage(const QPixmap& image);

    void clearChats();

    const QString& getLogin();
    const QString& getToken();
    const std::map<unsigned long,std::pair<QPixmap,QString>>& getChats();
    const QPixmap& getImage();

    static CurrentUser* getInstance();

private:
    CurrentUser();
    CurrentUser(const QString& userLogin, const QString& userToken)
        : login(userLogin), accessToken(userToken){}

    QString login;
    QString accessToken;
    QPixmap profileImg;
    std::map<unsigned long, std::pair<QPixmap,QString>> chats;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
