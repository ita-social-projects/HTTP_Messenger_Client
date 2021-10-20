#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "Logger.h"
#include <QMessageBox>

#define MIN_PASS_LENGTH 5
#define STATUS_OK "200"
#define STATUS_BAD_REQUEST "400"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::EchoMode::Password);
    ui->ConfirmPassword->setEchoMode(QLineEdit::EchoMode::Password);

    QRegularExpression rx("[a-zA-Z0-9]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->Login->setValidator(validator);

    ui->Login->setPlaceholderText(" Enter login:");
    ui->Password->setPlaceholderText(" Enter password:");
    ui->ConfirmPassword->setPlaceholderText(" Confirm password:");

    this->setWindowTitle("User registration");
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
    clearInfoFields();
    if(checkInput())
    {
        QString password = ui->Password->text();
        QString login = ui->Login->text();
        RequestManager::GetInstance()->signUp(login,password,this);
    }
}

void SignupWindow::clearInfoFields()
{
    LOG_DEBUG("Clearing fields");
    ui->Info->clear();
    ui->ConfPassInfo->clear();
    ui->PasswordInfo->clear();
    ui->LoginInfo->clear();
}

bool SignupWindow::checkInput()
{
    QString password = ui->Password->text();
    QString confPassword = ui->ConfirmPassword->text();

    if(isEmptyFields())
    {
       LOG_ERROR("Sign up fields is empty");
       printErrorText(ui->Info,"Some of registration lines are empty. Fill empty lines.");
       return false;
    }

    if(password.size() < MIN_PASS_LENGTH)
    {
        LOG_ERROR("Sign up password is too short");
        printErrorText(ui->PasswordInfo,"Your password should be at least 5 characters.");
        return false;
    }

    if(!isEqualPassword(password,confPassword))
    {
        LOG_ERROR("Sign up password inputs isn`t equals");
        printErrorText(ui->ConfPassInfo,"Your password inputs are not equal. Try again.");
        return false;
    }
    return true;
}

bool SignupWindow::isEmptyFields()
{
    QString password = ui->Password->text();
    QString confPassword = ui->ConfirmPassword->text();
    QString login = ui->Login->text();

    return login.isEmpty() || password.isEmpty() || confPassword.isEmpty();
}

void SignupWindow::printErrorText(QLabel *label,QString text)
{
    setErrorLabelColor(label);
    label->setText(text);
}

void SignupWindow::setErrorLabelColor(QLabel *label)
{
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::white);
    palette.setColor(label->foregroundRole(), Qt::red);
    label->setPalette(palette);
}

bool SignupWindow::isEqualPassword(const QString& pass,const QString& confPass)
{
    return pass == confPass;
}

void SignupWindow::onRequestFinished(QNetworkReply *answer, RequestType type)
{
    if (type == RequestType::SIGN_UP)
    {
        if (answer->error())
        {
            JsonDeserializer extractor;
            QJsonDocument document = QJsonDocument::fromJson(answer->readAll());
            QString resReply = extractor.extractMsg(document);
            LOG_ERROR(resReply.toStdString());
            QMessageBox::critical(nullptr, "ERROR", resReply);
        }
        else
        {
            LOG_DEBUG("Sign up success");
            QMessageBox::information(nullptr,"SUCCESS","You successfully registered");
            emit OpenLoginWindow();
        }
    }
}

