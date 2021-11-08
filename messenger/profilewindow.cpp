#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "imagemanager.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile");
    ui->label_Username->setText(CurrentUser::getInstance()->getLogin());
    ui->pushButton_UserImg->setIcon(CurrentUser::getInstance()->getImage());
    ui->pushButton_UserImg->setStyleSheet("background-color: rgb(230, 221, 238);");

    setPlaceholderTextToLabels();
    hideInfoFields();
    hideLoginFields();
    hidePasswordFields();

    //UserName widget animation block

        QPropertyAnimation *HideEditAnimation = new QPropertyAnimation(ui->Widget_SaveLogin, "maximumHeight");
        HideEditAnimation->setEasingCurve(QEasingCurve::OutBounce);
        HideEditAnimation->setDuration(1000);

        QPropertyAnimation *ShowEditAnimation = new QPropertyAnimation(ui->Widget_SaveLogin, "maximumHeight");
        HideEditAnimation->setEasingCurve(QEasingCurve::OutBounce);
        HideEditAnimation->setDuration(1000);

        QState *UserNameHidedState= new QState();
        UserNameHidedState->assignProperty(ui->Widget_SaveLogin,"maximumHeight",0);
        QState *UserNameShowedState= new QState();
        UserNameShowedState->assignProperty(ui->Widget_SaveLogin,"maximumHeight",84);

        QEventTransition *ShowUserNameTransition = new QEventTransition(ui->pushButton_ChangeUsername,QEvent::MouseButtonPress);
        ShowUserNameTransition->setTargetState(UserNameShowedState);
        ShowUserNameTransition->addAnimation(ShowEditAnimation);
        UserNameHidedState->addTransition(ShowUserNameTransition);

        QEventTransition *HideUserNameTransition = new QEventTransition(ui->pushButton_ChangeUsername,QEvent::MouseButtonPress);
        HideUserNameTransition->setTargetState(UserNameHidedState);
        HideUserNameTransition->addAnimation(HideEditAnimation);
        UserNameShowedState->addTransition(HideUserNameTransition);

        QStateMachine *UserNameMachine = new QStateMachine(this);
        UserNameMachine->setGlobalRestorePolicy(QStateMachine::RestoreProperties);
        UserNameMachine->addState(UserNameHidedState);
        UserNameMachine->addState(UserNameShowedState);
        UserNameMachine->setInitialState(UserNameHidedState);
        UserNameMachine->start();

    //Password widget animation block

        QPropertyAnimation *ShowPasswordEditAnimation = new QPropertyAnimation(ui->Widget_Password, "maximumHeight");
        ShowPasswordEditAnimation->setDuration(1000);
        ShowPasswordEditAnimation->setEasingCurve(QEasingCurve::OutBounce);

        QPropertyAnimation *HidePasswordEditAnimation = new QPropertyAnimation(ui->Widget_Password, "maximumHeight");
        HidePasswordEditAnimation->setDuration(1000);
        HidePasswordEditAnimation->setEasingCurve(QEasingCurve::OutBounce);

        QState *PasswordHidedState = new QState();
        PasswordHidedState->assignProperty(ui->Widget_Password,"maximumHeight",0);

        QState *PasswordShowedState = new QState();
        PasswordShowedState->assignProperty(ui->Widget_Password,"maximumHeight",179);


        QEventTransition *ShowPasswordTransition = new QEventTransition(ui->pushButton_ChangePassword,QEvent::MouseButtonPress);
        ShowPasswordTransition->setTargetState(PasswordShowedState);
        ShowPasswordTransition->addAnimation(ShowPasswordEditAnimation);
        PasswordHidedState->addTransition(ShowPasswordTransition);

        QEventTransition *HidePasswordTransition = new QEventTransition(ui->pushButton_ChangePassword,QEvent::MouseButtonPress);
        HidePasswordTransition->setTargetState(PasswordHidedState);
        HidePasswordTransition->addAnimation(HidePasswordEditAnimation);
        PasswordShowedState->addTransition(HidePasswordTransition);

        QStateMachine *PasswordMachine = new QStateMachine(this);
        PasswordMachine->setGlobalRestorePolicy(QStateMachine::RestoreProperties);
        PasswordMachine->addState(PasswordHidedState);
        PasswordMachine->addState(PasswordShowedState);
        PasswordMachine->setInitialState(PasswordHidedState);
        PasswordMachine->start();
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
    ui->label_PassInfo->hide();
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
    if(ui->pushButton_ChangeUsername->isChecked())
    {
        hideInfoFields();
        showLoginFields();
    }
    else
    {
        hideLoginFields();
    }
}

void ProfileWindow::showLoginFields()
{
    ui->lineEdit_Username->show();
    ui->pushButton_SaveLogin->show();
}

void ProfileWindow::on_pushButton_ChangePassword_clicked()
{
    if(ui->pushButton_ChangePassword->isChecked())
    {
        hideInfoFields();
        showPasswordFields();
    }
    else
    {
        hidePasswordFields();
    }
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
    if (!checkUsernameSame(newLogin))
    {
        return;
    }

    RequestManager::GetInstance()->updateLogin(CurrentUser::getInstance()->getToken(),newLogin,this);
}

void ProfileWindow::on_pushButton_SavePassword_clicked()
{
    QString password = ui->lineEdit_Password->text();
    QString newPassword = ui->lineEdit_NewPassword->text();
    QString newPassConf = ui->lineEdit_ConfNewPassword->text();

    hideInfoFields();

    if(!checkPasswordEqual(newPassword,newPassConf) ||
       !checkOldNewPasswordsEqual(password,newPassword))
    {
        return;
    }

    RequestManager::GetInstance()->updatePassword(CurrentUser::getInstance()->getToken(),password,newPassword,this);
}

bool ProfileWindow::checkUsernameSame(const QString& username)
{
   CurrentUser *user = CurrentUser::getInstance();
   if(username == user->getLogin())
   {
       setErrorLabelColor(ui->label_LoginInfo);
       ui->label_LoginInfo->show();
       ui->label_LoginInfo->setText("Your new username is the same as your previous");
       return false;
   }
   return true;
}

bool ProfileWindow::checkPasswordEqual(const QString& pass1, const QString& pass2)
{
    if(pass1 != pass2)
    {
       setErrorLabelColor(ui->label_ConfPassInfo);
       ui->label_ConfPassInfo->show();
       ui->label_ConfPassInfo->setText("Your password inputs are not equal. Try again.");
       return false;
    }
    return true;
}

bool ProfileWindow::checkOldNewPasswordsEqual(const QString& pass, const QString& newPass)
{
    if(pass == newPass)
    {
       setErrorLabelColor(ui->label_PassInfo);
       ui->label_PassInfo->show();
       ui->label_PassInfo->setText("Your new password is the same as your previous.");
       return false;
    }
    return true;
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
    if (reply->error())
    {
        JsonDeserializer extractor;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QString resReply = extractor.extractErrorMsg(document);
        QMessageBox::critical(nullptr, "ERROR", resReply);
    }
    else
    {
        if(type == RequestType::UPDATE_LOGIN)
        {
            CurrentUser *user = CurrentUser::getInstance();
            user->setLogin(ui->lineEdit_Username->text());
            ui->label_Username->setText(user->getLogin());
            ui->lineEdit_Username->clear();
            ui->lineEdit_Username->setPlaceholderText(user->getLogin());
            emit loginUpdated();
            QMessageBox::information(nullptr, "Profile", "Login was updated!");
            Cache::DeleteCacheFile();
            Cache::CreateIfNotExists(CurrentUser::getInstance()->getLogin());
        }
        if(type == RequestType::UPDATE_PASSWORD)
        {
            QMessageBox::information(nullptr, "Profile", "Password was updated!");
        }
        if(type == RequestType::DELETE_ACCOUNT)
        {
            emit accountDeleted();
            Cache::DeleteCacheFile();
            this->close();
        }
    }
}

void ProfileWindow::closeEvent(QCloseEvent * e )
{
    emit closing();
}

void ProfileWindow::on_pushButton_DeleteProfile_clicked()
{
    auto reply = QMessageBox::question(nullptr, "Profile Window", "If you delete your account then you can't restore it. "
                                                           "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        CurrentUser* user = CurrentUser::getInstance();
        RequestManager::GetInstance()->deleteAccount(user->getToken(), this);
    }
}

void ProfileWindow::on_pushButton_UserImg_clicked()
{
    ImageManager manager;
    QPixmap p = manager.uploadRoundedImage(this);
    if(p.isNull())
    {
        return;
    }

    ui->pushButton_UserImg->setIcon(p);
    ui->pushButton_UserImg->setStyleSheet("background-color: rgb(230, 221, 238);");
    CurrentUser::getInstance()->setImage(p);
    Cache::WriteUserImg();
    emit imageUpdated();
}
