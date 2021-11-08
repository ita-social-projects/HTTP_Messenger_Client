#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include "mainwindow.h"
#include "threadworker.h"
class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);

private slots:
    void open_LoginWindow();
    void open_SignupWindow();
    void open_MainWindow();
    void open_ProfileWindow();
    void open_CreateChatWindow();
    void open_ChatInfoWindow(CurrentChat chat);
    void open_EmojiList();

    void close_Window();
    void close_MinorWindow();

    void setIcon();
private:
    std::unique_ptr<QWidget> currentWindow;
    std::unique_ptr<QDialog> minorWindow;
    QIcon icon;
};
#endif // WINDOWMANAGER_H
