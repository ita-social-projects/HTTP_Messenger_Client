#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "currentUser.h"

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = nullptr);
    ~ProfileWindow();

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
