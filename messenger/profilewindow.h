#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "currentuser.h"
#include "requestmanager.h"
#include "jsondeserializer.h"
#include "cache.h"

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QDialog,  public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = nullptr);
    ~ProfileWindow();

    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;
private:
    bool checkUsernameSame(const QString& username);
    bool checkPasswordEqual(const QString& pass1, const QString& pass2);
    bool checkOldNewPasswordsEqual(const QString& pass, const QString& newPass);

    void setErrorLabelColor(QLabel *label);
    void setPlaceholderTextToLabels();

    void hideInfoFields();
    void hidePasswordFields();
    void hideLoginFields();

    void showPasswordFields();
    void showLoginFields();

signals:
    void closing();
    void accountDeleted();
    void loginUpdated();

private slots:
    void on_pushButton_ChangeUsername_clicked();
    void on_pushButton_ChangePassword_clicked();
    void on_pushButton_SaveLogin_clicked();
    void on_pushButton_SavePassword_clicked();
    void closeEvent(QCloseEvent * e) override;

    void on_pushButton_DeleteProfile_clicked();

private:
    Ui::ProfileWindow *ui;
};

#endif // PROFILEWINDOW_H
