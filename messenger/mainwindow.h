#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include "loginwindow.h"
#include "signupwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_window(QString user_name);

signals:
    void ExitButtonClicked();

private slots:
    void on_UsersList_itemClicked(QListWidgetItem *item);
    void on_SendButton_clicked();
    void on_SearchUserButton_clicked();
    void on_ExitButton_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
