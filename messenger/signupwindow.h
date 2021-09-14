#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QRegularExpressionValidator>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
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
