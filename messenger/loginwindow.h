#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "IWindowOpener.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QString GetLogin();
    QString GetPassword();
    void close_window();

signals:
    void LoginButton_signal();
    void SignupButton_signal();

private slots:
    void on_LoginButton_clicked();
    void on_SignupButton_clicked();

private:
    Ui::LoginWindow *ui;
    std::weak_ptr<IWindowOpener> WindowManager;
};

#endif // LOGINWINDOW_H
