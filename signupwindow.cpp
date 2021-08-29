#include "signupwindow.h"
#include "ui_signupwindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    ui->EnterPassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->EnterPasswordAgain->setEchoMode(QLineEdit::EchoMode::Password);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

QString SignupWindow::GetLogin()
{
    return ui->EnterLogin->text();
}


QString SignupWindow::GetPassword()
{
    return ui->EnterPassword->text();
}

QString SignupWindow::GetPasswordAgain()
{
    return ui->EnterPasswordAgain->text();
}

void SignupWindow::close_window()
{
    this->close();
    ui->EnterLogin->clear();
    ui->EnterPassword->clear();
    ui->EnterPasswordAgain->clear();
}

void SignupWindow::on_SignupButton_clicked()
{
    emit SignupButton_signal();
}


void SignupWindow::on_LoginButton_clicked()
{
    emit LoginButton_signal();
}

