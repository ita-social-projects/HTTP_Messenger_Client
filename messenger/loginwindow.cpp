#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

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
        // get JsonDocument
        QString answer = get("/login"); // post
        if (answer=="SUCCESS")
        {
            QMessageBox::about(nullptr, "SUCCESS", "Congratulations! Everything is ok!");
            emit LoginSuccess(ui->EnterLogin->text());
        }
        if (answer == "NO ANSWER")
        {
            QMessageBox::critical(nullptr, "ERROR", "Opps! Check your Internet connection!");
        }
        if (answer == "ERROR")
        {
            QMessageBox::critical(nullptr, "ERROR", "Opps! Some technical problems... Please, try again later!");
        }
        if (answer == "FAIL")
        {
            QMessageBox::critical(nullptr, "ERROR", "Opps! Invalid login or password!");
        }
    }
}

void LoginWindow::on_SignupButton_clicked()
{
    emit OpenSignupWindow();
}

void LoginWindow::ClearInfoFields()
{
    ui->Info->clear();
}

bool LoginWindow::CheckInput()
{
    QPalette palette = ui->Info->palette();

    QString password = ui->EnterPassword->text();
    QString login = ui->EnterLogin->text();

    if(login.isEmpty() ||
       password.isEmpty())
    {
       palette.setColor(ui->Info->backgroundRole(), Qt::white);
       palette.setColor(ui->Info->foregroundRole(), Qt::red);
       ui->Info->setPalette(palette);
       ui->Info->setText("Some of registration lines are empty. Fill empty lines.");
       return false;
    }
    return true;
}
