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
        QString password = ui->EnterPassword->text();
        QString login = ui->EnterLogin->text();

        //emit LoginSuccess(ui->EnterLogin->text());
        RequestManager::GetInstance()->login(login,password, this);
    }
}

void LoginWindow::OnRequestFinished(QNetworkReply *answer)
{
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
            // User user = answer.extact(document, "/login") ???
            QMessageBox::about(nullptr, "SUCCESS", "Congratulations! Everything is ok!");
            emit LoginSuccess(ui->EnterLogin->text());
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
