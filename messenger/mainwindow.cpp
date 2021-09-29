#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QString user_name)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UserName->setText(user_name);

    ui->EnterMessage->setPlaceholderText(" Enter message:");
    ui->SearchUser->setPlaceholderText(" Enter user to search:");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkNewMessages()
{
    while (true)
    {
//        QNetworkReply* answer = get("/new_message");
//        if (answer != nullptr)
//        {
//            if (!answer->error())
//            {
//                // show message
//            }
//            answer->deleteLater();
//        }
        QThread::sleep(1);
    }
}

void MainWindow::on_UsersList_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_SendButton_clicked()
{
    // get JsonDocument
//    QNetworkReply* answer = get("/send"); // post
//    if (answer == nullptr || answer->error())
//    {
//        // show "wasn't sended"
//    }
//    else
//    {
//        // show message
//        answer->deleteLater();
//    }
}

void MainWindow::on_SearchUserButton_clicked()
{
    // get JsonDocument
//    QNetworkReply* answer = get("/search"); // post
//    if (answer == nullptr || answer->error())
//    {
//        // show "Not Found"
//    }
//    else
//    {
//        // show list
//        answer->deleteLater();
//    }
}

void MainWindow::on_ExitButton_clicked()
{
    emit ExitButtonClicked();
}
