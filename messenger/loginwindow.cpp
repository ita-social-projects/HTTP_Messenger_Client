#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->EnterPassword->setEchoMode(QLineEdit::EchoMode::Password);

    QRegularExpression rx("[a-zA-Z]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->EnterLogin->setValidator(validator);

    ui->EnterLogin->setPlaceholderText(" Enter login:");
    ui->EnterPassword->setPlaceholderText(" Enter password:");

    delete validator;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    ClearInfoFields();
    if(CheckInput())
    {
        //save information about user
        //send it to a server
        emit LoginSuccess(ui->EnterLogin->text());
    }
}

void LoginWindow::on_SignupButton_clicked()
{
    emit OpenSignupWindow();
}

void LoginWindow::ClearInfoFields()
{

}

bool LoginWindow::CheckInput()
{
    QString password = ui->EnterPassword->text();
    QString login = ui->EnterLogin->text();

    if(login.isEmpty() ||
       password.isEmpty())
    {
       return false;
    }

    return true;
}
