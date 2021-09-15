#include "userinterface.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include "mainwindow.h"

UserInterface::UserInterface(QObject *parent) : QObject(parent), current_window(nullptr)
{
    open_LoginWindow();
}
UserInterface::~UserInterface()
{
    delete current_window;
}
void UserInterface::open_LoginWindow()
{
    if(current_window != nullptr)
    {
        current_window->close();
        delete current_window;
    }
    current_window = new LoginWindow();
    connect(current_window, SIGNAL(OpenSignupWindow()), this, SLOT(open_SignupWindow()));
    connect(current_window, SIGNAL(LoginSuccess()), this, SLOT(open_MainWindow()));
    current_window->show();
}
void UserInterface::open_SignupWindow()
{
    current_window->close();
    delete current_window;
    current_window = new SignupWindow();
    connect(current_window, SIGNAL(OpenLoginWindow()), this, SLOT(open_LoginWindow()));
    connect(current_window, SIGNAL(SignupSuccess()), this, SLOT(open_MainWindow()));
    current_window->show();
}
void UserInterface::open_MainWindow()
{
    current_window->close();
    delete current_window;
    current_window = new MainWindow();
    connect(current_window, SIGNAL(ExitButtonClicked()), this, SLOT(open_LoginWindow()));
    current_window->show();
}
