#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include "mainwindow.h"

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
    void open_CreateChatWindow(MainWindow* ptr);
    void open_ChatInfoWindow();

    void close_Window();
    void close_MinorWindow();

private:
    std::unique_ptr<QWidget> currentWindow;
    std::unique_ptr<QDialog> minorWindow;
};
#endif // WINDOWMANAGER_H
