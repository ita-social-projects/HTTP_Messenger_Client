#include "windowmanager.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include "mainwindow.h"
#include "Logger.h"


WindowManager::WindowManager(QObject *parent) : QObject(parent), current_window(nullptr)
{
    if(Cache::OpenByCache() == "")
    {
        open_LoginWindow();
    }
    else
    {
        open_MainWindow(Cache::OpenByCache());
    }
}
void WindowManager::open_LoginWindow()
{
    LOG_DEBUG("Opening login window");
    close_Window();
    current_window.reset(new LoginWindow());
    connect(current_window.get(), SIGNAL(OpenSignupWindow()), this, SLOT(open_SignupWindow()));
    connect(current_window.get(), SIGNAL(LoginSuccess(QString)), this, SLOT(open_MainWindow(QString)));

    current_window->show();
}
void WindowManager::open_SignupWindow()
{
    LOG_DEBUG("Opening sign up window");
    close_Window();
    current_window.reset(new SignupWindow());
    connect(current_window.get(), SIGNAL(OpenLoginWindow()), this, SLOT(open_LoginWindow()));
    current_window->show();
}
void WindowManager::open_MainWindow(QString user_name)
{
    LOG_DEBUG("Opening main window");
    close_Window();
    Cache::CreateIfNotExists(user_name);
    current_window.reset(new MainWindow(user_name));
    connect(current_window.get(), SIGNAL(SignoutButtonClicked()), this, SLOT(open_LoginWindow()));
    current_window->show();
}
void WindowManager::close_Window()
{
    if(current_window)
    {
        LOG_DEBUG("Closing current window");
        current_window->close();
    }
    else
    {
        LOG_ERROR("Current window pointer is empty");
    }
}
