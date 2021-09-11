#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include"IWindowOpener.h"
#include <QMainWindow>

#include "loginwindow.h"
#include "signupwindow.h"
#include <QWidget>


class WindowManager: public IWindowOpener
{
public:
    WindowManager(QWidget);
    virtual void OpenMainWindow();
    virtual void OpenLoginWindow();
    virtual void OpenSignupindow();
private:

    std::unique_ptr<QWidget> currentWindow(QWidget);

};

#endif // WINDOWMANAGER_H
