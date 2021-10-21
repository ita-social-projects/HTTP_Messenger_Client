#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "requestmanager.h"
#include "JsonDeserializer.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool CheckInput();
    void ClearInfoFields();

    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

signals:
    void LoginSuccess();
    void OpenSignupWindow();

private slots:
    void on_LoginButton_clicked();
    void on_SignupButton_clicked();

private:
    QValidator *validator;
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
