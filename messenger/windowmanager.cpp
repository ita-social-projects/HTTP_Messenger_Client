#include "windowmanager.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include "mainwindow.h"

WindowManager::WindowManager(QObject *parent) : QObject(parent), current_window(nullptr)
{
    open_LoginWindow();
}
WindowManager::~WindowManager()
{

}
void WindowManager::open_LoginWindow()
{
    if(current_window)
    {
        current_window->close();
    }
    current_window.reset(new LoginWindow());
    connect(current_window.get(), SIGNAL(OpenSignupWindow()), this, SLOT(open_SignupWindow()));
    connect(current_window.get(), SIGNAL(LoginSuccess(QString)), this, SLOT(open_MainWindow(QString)));
    current_window->show();
}
void WindowManager::open_SignupWindow()
{
    if(current_window)
    {
        current_window->close();
    }
    current_window.reset(new SignupWindow());
    connect(current_window.get(), SIGNAL(OpenLoginWindow()), this, SLOT(open_LoginWindow()));
    connect(current_window.get(), SIGNAL(SignupSuccess(QString)), this, SLOT(open_MainWindow(QString)));
    current_window->show();
}
void WindowManager::open_MainWindow(QString user_name)
{
    if(current_window)
    {
        current_window->close();
    }
    current_window.reset(new MainWindow(user_name));
    connect(current_window.get(), SIGNAL(ExitButtonClicked()), this, SLOT(open_LoginWindow()));
    current_window->show();
}
