#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "Logger.h"
#include "cache.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->EnterPassword->setEchoMode(QLineEdit::EchoMode::Password);

    QRegularExpression rx("[a-zA-Z0-9]+");
    validator = new QRegularExpressionValidator(rx, this);
    ui->EnterLogin->setValidator(validator);

    ui->EnterURL->setPlaceholderText(" Enter URL to connect:");
    ui->EnterLogin->setPlaceholderText(" Enter login:");
    ui->EnterPassword->setPlaceholderText(" Enter password:");

    this->setWindowTitle("Log In");
}

LoginWindow::~LoginWindow()
{
    delete validator;
    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    LOG_DEBUG("Login button clicked");
    ClearInfoFields();
    if(CheckInput())
    {
        QUrl url = ui->EnterURL->text();
        if(url.isValid())
        {
            RequestManager::GetInstance()->setServerURL(url);
        }
        QString password = ui->EnterPassword->text();
        QString login = ui->EnterLogin->text();
        RequestManager::GetInstance()->login(login, password, this);
    }
}

void LoginWindow::onRequestFinished(QNetworkReply *answer, RequestType type)
{
    if(type == RequestType::LOG_IN)
    {
        JsonDeserializer extractor;
        QJsonDocument document = QJsonDocument::fromJson(answer->readAll());
        if (answer->error())
        {
            QString resReply = extractor.extractErrorMsg(document);
            LOG_ERROR(resReply.toStdString());
            QMessageBox::critical(nullptr, "ERROR", "Can`t connect to server\n" + resReply);
        }
        else
        {
            LOG_DEBUG("Login success");
            CurrentUser* user = extractor.extractUserInfo(document);
            Cache::CreateIfNotExists(user->getLogin());
            emit LoginSuccess();
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
    QUrl url = ui->EnterURL->text();

    if(login.isEmpty() ||
       password.isEmpty() || url.isEmpty())
    {
       LOG_ERROR("Some of lines are empty");
       palette.setColor(ui->Info->backgroundRole(), Qt::white);
       palette.setColor(ui->Info->foregroundRole(), Qt::red);
       ui->Info->setPalette(palette);
       ui->Info->setText("Some of lines are empty. Fill empty lines.");
       return false;
    }
    return true;
}
