#include "profilewindow.h"
#include "ui_profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile");
    ui->label_Username->setText(CurrentUser::getInstance()->getLogin());

    setPlaceholderTextToLabels();
    hideInfoFields();
    hideLoginFields();
    hidePasswordFields();
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::setPlaceholderTextToLabels()
{
    CurrentUser *user = CurrentUser::getInstance();
    ui->lineEdit_Username->setPlaceholderText(user->getLogin());
    ui->lineEdit_Password->setPlaceholderText(" Enter your password:");
    ui->lineEdit_NewPassword->setPlaceholderText(" Enter new password:");
    ui->lineEdit_ConfNewPassword->setPlaceholderText(" Confirm new password:");
}

void ProfileWindow::hideInfoFields()
{
    ui->label_LoginInfo->hide();
    ui->label_ConfPassInfo->hide();
}

void ProfileWindow::hideLoginFields()
{
    ui->lineEdit_Username->hide();
    ui->pushButton_SaveLogin->hide();
}

void ProfileWindow::hidePasswordFields()
{
    ui->lineEdit_Password->hide();
    ui->lineEdit_NewPassword->hide();
    ui->lineEdit_ConfNewPassword->hide();
    ui->pushButton_SavePassword->hide();
}

void ProfileWindow::on_pushButton_ChangeUsername_clicked()
{
    hidePasswordFields();
    hideInfoFields();
    showLoginFields();
}

void ProfileWindow::showLoginFields()
{
    ui->lineEdit_Username->show();
    ui->pushButton_SaveLogin->show();
}

void ProfileWindow::on_pushButton_ChangePassword_clicked()
{
    hideLoginFields();
    hideInfoFields();
    showPasswordFields();
}

void ProfileWindow::showPasswordFields()
{
    ui->lineEdit_Password->show();
    ui->lineEdit_NewPassword->show();
    ui->lineEdit_ConfNewPassword->show();
    ui->pushButton_SavePassword->show();
}

void ProfileWindow::on_pushButton_SaveLogin_clicked()
{
    QString newLogin = ui->lineEdit_Username->text();

    hideInfoFields();
    checkUsernameSame(newLogin);
    //RequestManager::GetInstance()->UpdateLogin(CurrentUser::GetToken(),newLogin);
}

void ProfileWindow::on_pushButton_SavePassword_clicked()
{
    QString password = ui->lineEdit_Password->text();
    QString newPassword = ui->lineEdit_NewPassword->text();
    QString newPassConf = ui->lineEdit_ConfNewPassword->text();

    hideInfoFields();
    checkPasswordEqual(newPassword,newPassConf);
    checkOldNewPasswordsEqual(password,newPassword);

    //RequestManager::GetInstance()->UpdatePassword(CurrentUser::GetToken(),password,newPassword);
}

void ProfileWindow::checkUsernameSame(const QString& username)
{
   CurrentUser *user = CurrentUser::getInstance();
   if(username == user->getLogin())
   {
       setErrorLabelColor(ui->label_LoginInfo);
       ui->label_LoginInfo->show();
       ui->label_LoginInfo->setText("Your new username is the same as your previous");
   }
}

void ProfileWindow::checkPasswordEqual(const QString& pass1, const QString& pass2)
{
    if(pass1 != pass2)
    {
       setErrorLabelColor(ui->label_ConfPassInfo);
       ui->label_ConfPassInfo->show();
       ui->label_ConfPassInfo->setText("Your password inputs are not equal. Try again.");
    }
}

void ProfileWindow::checkOldNewPasswordsEqual(const QString& pass, const QString& newPass)
{
    if(pass == newPass)
    {
       setErrorLabelColor(ui->label_ConfPassInfo);
       ui->label_ConfPassInfo->show();
       ui->label_ConfPassInfo->setText("Your new password is the same as your previous.");
    }
}

void ProfileWindow::setErrorLabelColor(QLabel *label)
{
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::white);
    palette.setColor(label->foregroundRole(), Qt::red);
    label->setPalette(palette);
}

void ProfileWindow::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    JsonDeserializer extractor;
    if (reply->error())
    {
         QMessageBox::critical(nullptr, "ERROR", "Connection failed! Please, try again!");
    }
    else
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QString resReply = extractor.extractMsg(document);
        QMessageBox::information(nullptr,"Profile",resReply);
    }

}
