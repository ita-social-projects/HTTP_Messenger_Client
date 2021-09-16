#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "signupinfo.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::EchoMode::Password);
    ui->ConfirmPassword->setEchoMode(QLineEdit::EchoMode::Password);

    QRegularExpression rx("[a-zA-Z]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Login->setValidator(validator);

    ui->Login->setPlaceholderText(" Enter login:");
    ui->Password->setPlaceholderText(" Enter password:");
    ui->ConfirmPassword->setPlaceholderText(" Confirm password:");

    delete validator;
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_LoginButton_clicked()
{
    emit OpenLoginWindow();
}

void SignupWindow::on_SignUp_clicked()
{
    ClearInfoFields();
    if(CheckInput())
    {
        SignUpInfo info;
        info.send(info.pack());
        emit SignupSuccess(ui->Login->text());
    }
}

void SignupWindow::ClearInfoFields()
{
    ui->Info->clear();
    ui->ConfPassInfo->clear();
    ui->PasswordInfo->clear();
    ui->LoginInfo->clear();
}

bool SignupWindow::CheckInput()
{
    QPalette palette = ui->Info->palette();
    QString password = ui->Password->text();
    QString confPassword = ui->ConfirmPassword->text();
    QString login = ui->Login->text();

    if(login.isEmpty() ||
       password.isEmpty() ||
       confPassword.isEmpty())
    {
       palette.setColor(ui->Info->backgroundRole(), Qt::white);
       palette.setColor(ui->Info->foregroundRole(), Qt::red);
       ui->Info->setPalette(palette);
       ui->Info->setText("Some of registration lines are empty. Fill empty lines.");
       return false;
    }

    if(password.size() < 5)
    {
        palette.setColor(ui->PasswordInfo->backgroundRole(), Qt::white);
        palette.setColor(ui->PasswordInfo->foregroundRole(), Qt::red);
        ui->PasswordInfo->setPalette(palette);
        ui->PasswordInfo->setText("Your password should be at least 5 characters.");
        return false;
    }

    if(password != confPassword)
    {
        palette.setColor(ui->ConfPassInfo->backgroundRole(), Qt::white);
        palette.setColor(ui->ConfPassInfo->foregroundRole(), Qt::red);
        ui->ConfPassInfo->setPalette(palette);
        ui->ConfPassInfo->setText("Your password inputs are not equel. Try again.");
        return false;
    }

    return true;
}
