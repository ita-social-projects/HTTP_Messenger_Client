#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QWidget>
#include "cache.h"

class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);

private slots:
    void open_LoginWindow();
    void open_SignupWindow();
    void open_MainWindow(QString user_name);
    void close_Window();

private:
    std::unique_ptr<QWidget> current_window;
};
#endif // WINDOWMANAGER_H
