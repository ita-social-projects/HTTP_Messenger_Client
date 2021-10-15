#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "currentUser.h"
#include "requestmanager.h"
#include "replyMsgExtractor.h"
#include "userinfoExtractor.h"

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
    void checkUsernameSame();
    void checkPasswordEqual();

    void setErrorLabelColor(QLabel *label);
    void setPlaceholderTextToLabels();

    void hideInfoFields();
    void hidePasswordFields();
    void hideLoginFields();

    void showPasswordFields();
    void showLoginFields();

private slots:
    void on_pushButton_ChangeUsername_clicked();

    void on_pushButton_ChangePassword_clicked();

    void on_pushButton_SaveLogin_clicked();

    void on_pushButton_SavePassword_clicked();

private:
    Ui::ProfileWindow *ui;
};

#endif // PROFILEWINDOW_H
