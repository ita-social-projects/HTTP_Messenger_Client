#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QtWidgets>

#include "currentuser.h"
#include "requestmanager.h"
#include "jsondeserializer.h"
#include "cache.h"
#include "QtStateMachine/QEventTransition"
#include "QtStateMachine/QtStateMachine"
#include "QPropertyAnimation"
#include "QSequentialAnimationGroup"

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
    const QPixmap roundImage(const QPixmap &pix);

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

private slots:
    void on_pushButton_ChangeUsername_clicked();
    void on_pushButton_ChangePassword_clicked();
    void on_pushButton_SaveLogin_clicked();
    void on_pushButton_SavePassword_clicked();
    void closeEvent(QCloseEvent * e) override;
    void on_pushButton_DeleteProfile_clicked();
    void on_pushButton_UserImg_clicked();

private:
    Ui::ProfileWindow *ui;
    QIcon accountImage;
};

#endif// PROFILEWINDOW_H
