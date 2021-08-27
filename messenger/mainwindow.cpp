#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , main_w(new Ui::MainWindow)
{
    connect(&log_w, SIGNAL(LoginButton_signal()), this, SLOT(logging()));
    connect(&log_w, SIGNAL(SignupButton_signal()), this, SLOT(SignupWindow_open()));
    connect(&sign_w, SIGNAL(LoginButton_signal()), this, SLOT(LoginWindow_open()));
    connect(&sign_w, SIGNAL(SignupButton_signal()), this, SLOT(registration()));

    main_w->setupUi(this);
    main_w->ShowOrHideChatButton->setCheckable(true);
    main_w->ShowOrHideProfileButton->setCheckable(true);
    main_w->ShowOrHideChatButton->setChecked(true);
    main_w->ShowOrHideProfileButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete main_w;
}

void MainWindow::display()
{
    log_w.show();
}

void MainWindow::close_window()
{
    this->close();
    main_w->UserName->clear();
    main_w->ChatName->clear();
    main_w->EnterMessage->clear();
    main_w->SearchUser->clear();
    main_w->UsersList->clear();
    main_w->Messages->clear();
}

void MainWindow::LoginWindow_open()
{
    log_w.show();
    sign_w.close_window();
}

void MainWindow::SignupWindow_open()
{
    sign_w.show();
    log_w.close_window();
}

void MainWindow::logging()
{
    // request to server
    QString server_answer = "Success";
    if(server_answer == "Success")
    {
        main_w->UserName->setText(log_w.GetLogin());
        this->show();
        log_w.close_window();
    }
}

void MainWindow::registration()
{
    QString pass1 = sign_w.GetPassword();
    QString pass2 = sign_w.GetPasswordAgain();
    if(pass1 != pass2)
    {
        QMessageBox::warning(this, "ERROR","Invalid login or password!");

    }
    // request to server
    QString server_answer = "Success";
    if(server_answer == "Success")
    {
        log_w.show();
        sign_w.close_window();
    }
}

void MainWindow::on_UsersList_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_SendButton_clicked()
{

}

void MainWindow::on_SearchUserButton_clicked()
{

}

void MainWindow::on_ExitButton_clicked()
{
    log_w.show();
    this->close_window();
}


void MainWindow::on_ShowOrHideProfileButton_clicked()
{
    if(main_w->ShowOrHideProfileButton->isChecked()){
        main_w->ProfileWidget->show();
    }
    else
    {
        main_w->ProfileWidget->hide();
    }
}


void MainWindow::on_ShowOrHideChatButton_clicked()
{
    if(main_w->ShowOrHideChatButton->isChecked()){
        main_w->ChatsWidget->show();
    }
    else
    {
        main_w->ChatsWidget->hide();
    }
}

