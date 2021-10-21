#include "windowmanager.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include "Logger.h"
#include "profilewindow.h"
#include "cache.h"
#include "createchat.h"
#include "chatinfo.h"

WindowManager::WindowManager(QObject *parent) : QObject(parent), currentWindow(nullptr), minorWindow(nullptr)
{
    setIcon();
    if(Cache::OpenByCache() == "")
    {
        open_LoginWindow();
    }
    else
    {
        open_MainWindow();
    }
}

void WindowManager::setIcon()
{
    this->icon = QIcon(":/icons/icons/messenger1.ico");
}

void WindowManager::open_LoginWindow()
{
    LOG_DEBUG("Opening login window");
    close_Window();
    currentWindow.reset(new LoginWindow());
    currentWindow->setWindowIcon(this->icon);
    connect(currentWindow.get(), SIGNAL(OpenSignupWindow()), this, SLOT(open_SignupWindow()));
    connect(currentWindow.get(), SIGNAL(LoginSuccess()), this, SLOT(open_MainWindow()));

    currentWindow->show();
}
void WindowManager::open_SignupWindow()
{
    LOG_DEBUG("Opening sign up window");
    close_Window();
    currentWindow.reset(new SignupWindow());
    currentWindow->setWindowIcon(this->icon);
    connect(currentWindow.get(), SIGNAL(OpenLoginWindow()), this, SLOT(open_LoginWindow()));
    currentWindow->show();
}
void WindowManager::open_MainWindow()
{
    LOG_DEBUG("Opening main window");
    close_Window();
    currentWindow.reset(new MainWindow());
    currentWindow->setWindowIcon(this->icon);
    connect(currentWindow.get(), SIGNAL(SignoutButtonClicked()), this, SLOT(open_LoginWindow()));
    connect(currentWindow.get(), SIGNAL(openProfileWindow()), this, SLOT(open_ProfileWindow()));
    connect(currentWindow.get(), SIGNAL(openCreateChatWindow()), this, SLOT(open_CreateChatWindow()));
    connect(currentWindow.get(), SIGNAL(openChatInfo()), this, SLOT(open_ChatInfoWindow()));
    currentWindow->show();
}

void WindowManager::open_ProfileWindow()
{
    minorWindow.reset(new ProfileWindow());
    minorWindow->setWindowIcon(this->icon);
    connect(minorWindow.get(), SIGNAL(closing()), this, SLOT(close_MinorWindow()));
    minorWindow->setModal(true);
    minorWindow->show();
}

void WindowManager::open_ChatInfoWindow()
{
    minorWindow.reset(new ChatInfo());
    minorWindow->setWindowIcon(this->icon);
    connect(minorWindow.get(), SIGNAL(closing()), this, SLOT(close_MinorWindow()));
    connect(minorWindow.get(), SIGNAL(leaveChat()), currentWindow.get(), SLOT(leaveChat()));
    minorWindow->setModal(true);
    minorWindow->show();
}

void WindowManager::open_CreateChatWindow()
{
    minorWindow.reset(new CreateChat());
    minorWindow->setWindowIcon(this->icon);
    connect(minorWindow.get(), SIGNAL(addChat()), currentWindow.get(), SLOT(addNewChat()));
    connect(minorWindow.get(), SIGNAL(closing()), this, SLOT(close_MinorWindow()));
    minorWindow->setModal(true);
    minorWindow->show();
}

void WindowManager::close_MinorWindow()
{
    minorWindow.reset(nullptr);
}

void WindowManager::close_Window()
{
    if(currentWindow)
    {
        LOG_DEBUG("Closing current window");
        currentWindow->close();
    }
    else
    {
        LOG_ERROR("Current window pointer is empty");
    }
}
