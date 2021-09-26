#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QRegularExpressionValidator>
#include <requestmanager.h>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget, public RequestManager
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
    QString GetLogin();
    QString GetPassword();
    QString GetConfirmPassword();
    void CheckIfUserAlreadyRegistered();
    bool CheckInput();
    void ClearInfoFields();

signals:
    void OpenLoginWindow();
    void SignupSuccess(QString);

private slots:
    void on_LoginButton_clicked();
    void on_SignUp_clicked();

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H
