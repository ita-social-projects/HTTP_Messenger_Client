#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->EnterPassword->setEchoMode(QLineEdit::EchoMode::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::GetLogin()
{
    return ui->EnterLogin->text();
}


QString LoginWindow::GetPassword()
{
    return ui->EnterPassword->text();
}

void LoginWindow::close_window()
{
    this->close();
    ui->EnterLogin->clear();
    ui->EnterPassword->clear();
}

void LoginWindow::on_LoginButton_clicked()
{
    emit LoginButton_signal();
}


void LoginWindow::on_SignupButton_clicked()
{
    emit SignupButton_signal();
}

