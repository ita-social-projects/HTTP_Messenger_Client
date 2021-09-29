#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "requestmanager.h"
#include "replymsgkeeper.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
    void CheckIfUserAlreadyRegistered();
    bool CheckInput();
    void ClearInfoFields();


    virtual void OnRequestFinished(QNetworkReply *reply) override;

private:
    void PrintErrorText(QLabel *label,QString text);
    void SetErrorLabelColor(QLabel *label);
    bool IsEqualPassword(QString& pass, QString& confPass);
    bool IsEmptyFields();

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
