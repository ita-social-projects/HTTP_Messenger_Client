#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include "requestmanager.h"
#include <mutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public RequestManager::RequestResultInterface
{
    Q_OBJECT

public:
    MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();

    void showMessage(QString from, QString message, QString date, QString time);
    virtual void onRequestFinished(QNetworkReply *reply, RequestType type) override;

private:
    bool CheckMessage();

signals:
    void SignoutButtonClicked();
    void openProfileWindow();
    void openCreateChatWindow(MainWindow *ptr);
    void openChatInfo();

private slots:
    void on_ChatList_itemClicked(QListWidgetItem *item);
    void on_SendButton_clicked();
    void on_UserImg_clicked();
    void on_CreateChat_clicked();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionExit_triggered();
    void on_actionProfile_triggered();
    void on_actionSign_out_triggered();
    void on_ChatInfo_clicked();
    void on_SearchChat_textEdited(const QString &arg1);
    void addNewChat();

private:
    Ui::MainWindow *ui;
    static std::mutex mtx;
};
#endif // MAINWINDOW_H

