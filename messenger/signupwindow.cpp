#include "signupwindow.h"
#include "ui_signupwindow.h"

#define MIN_PASS_LENGTH 5

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
        QString password = ui->Password->text();
        QString login = ui->Login->text();
        RequestManager::GetInstance()->signUp(login,password,this);
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
    QString password = ui->Password->text();
    QString confPassword = ui->ConfirmPassword->text();

    if(IsEmptyFields())
    {
       PrintErrorText(ui->Info,"Some of registration lines are empty. Fill empty lines.");
       return false;
    }

    if(password.size() < MIN_PASS_LENGTH)
    {
        PrintErrorText(ui->PasswordInfo,"Your password should be at least 5 characters.");
        return false;
    }

    if(!IsEqualPassword(password,confPassword))
    {
        PrintErrorText(ui->ConfPassInfo,"Your password inputs are not equel. Try again.");
        return false;
    }

    return true;
}

bool SignupWindow::IsEmptyFields()
{
    QString password = ui->Password->text();
    QString confPassword = ui->ConfirmPassword->text();
    QString login = ui->Login->text();

    return login.isEmpty() || password.isEmpty() || confPassword.isEmpty();
}

void SignupWindow::PrintErrorText(QLabel *label,QString text)
{
    SetErrorLabelColor(label);
    label->setText(text);
}

void SignupWindow::SetErrorLabelColor(QLabel *label)
{
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::white);
    palette.setColor(label->foregroundRole(), Qt::red);
    label->setPalette(palette);
}

bool SignupWindow::IsEqualPassword(QString& pass, QString& confPass)
{
    return pass == confPass;
}

void SignupWindow::OnRequestFinished(QNetworkReply *answer)
{
    ReplyMsgKeeper replyMsg;
    if (answer == nullptr)
    {
        QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
    }
    else
    {
        if (answer->error())
        {
            QMessageBox::critical(nullptr, "ERROR", "Invalid login or password!");
        }
        else
        {
            QJsonDocument document = QJsonDocument::fromJson(answer->readAll());
            QString resMsg = replyMsg.extract(document);
            // check status code;
            QMessageBox::about(nullptr, "SUCCESS", "Congratulations! Everything is ok!");
            emit SignupSuccess(ui->Login->text());
        }
    }
}
