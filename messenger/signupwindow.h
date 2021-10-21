#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "requestmanager.h"
#include "JsonDeserializer.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
    void checkIfUserAlreadyRegistered();
    bool checkInput();
    void clearInfoFields();

    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

private:
    void printErrorText(QLabel *label, QString text);
    void setErrorLabelColor(QLabel *label);
    bool isEqualPassword(const QString& pass,const QString& confPass);
    bool isEmptyFields();

signals:
    void OpenLoginWindow();

private slots:
    void on_LoginButton_clicked();
    void on_SignUp_clicked();

private:
    QValidator *validator;
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H
