#include "threadworker.h"
#include "jsondeserializer.h"
#include "Logger.h"

ThreadWorker::ThreadWorker(MainWindow& mW)
    :QObject(nullptr)
{
    mainWindow = &mW;
    mt = new M_Thread(mainWindow, this);
}

void ThreadWorker::StartThread()
{
    mt->start();
}

M_Thread::M_Thread(MainWindow* mW, ThreadWorker* mU)
{
    mainWindow = mW;
    messagesUpdater = mU;
    connect(this, SIGNAL(SendRequests()), mainWindow, SLOT(UpdateData()));
    connect(mainWindow, &MainWindow::finished, this, &M_Thread::terminate);
}
void M_Thread::run()
{
    while (true)
    {
        emit SendRequests();
        QThread::sleep(1);
        LOG_DEBUG("Messages Update");
    }
}
