#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
