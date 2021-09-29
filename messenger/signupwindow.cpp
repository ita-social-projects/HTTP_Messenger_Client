#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QMessageBox>

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
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

QString SignupWindow::GetLogin()
{
    return ui->Login->text();
}

QString SignupWindow::GetPassword()
{
    return ui->Password->text();
}

QString SignupWindow::GetConfirmPassword()
{
    return ui->ConfirmPassword->text();
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
        // get JsonDocument
        QNetworkReply* answer = get("/signup"); // post
        if (answer == nullptr)
        {
            QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
        }
        else
        {
            if (answer->error())
            {
                QMessageBox::critical(nullptr, "ERROR", "This account already exist!");
            }
            else
            {
                QJsonDocument document = QJsonDocument::fromJson(answer->readAll());
                // User user = answer.extact(document, "/signup") ???
                QMessageBox::about(nullptr, "SUCCESS", "Congratulations! Everything is ok!");
                emit SignupSuccess(ui->Login->text());
            }
            answer->deleteLater();
        }
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

    QString password = GetPassword();
    QString confPassword = GetConfirmPassword();
    QString login = GetLogin();

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
