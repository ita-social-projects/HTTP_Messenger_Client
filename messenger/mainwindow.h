
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include "loginwindow.h"
#include "signupwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();
    void close_window();

private slots:
    void on_SendButton_clicked();
    void on_SearchUserButton_clicked();
    void on_ExitButton_clicked();

    void LoginWindow_open();
    void SignupWindow_open();
    void logging();
    void registration();

    void on_ShowOrHideProfileButton_clicked();

private:
    Ui::MainWindow *main_w;
    LoginWindow log_w;
    SignupWindow sign_w;
};
#endif // MAINWINDOW_H

