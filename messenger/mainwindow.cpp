#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::show_window(QString user_name)
{
    ui->UserName->setText(user_name);
    this->show();
}

void MainWindow::on_UsersList_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_SendButton_clicked()
{

}

void MainWindow::on_SearchUserButton_clicked()
{

}

void MainWindow::on_ExitButton_clicked()
{
    emit ExitButtonClicked();
}
