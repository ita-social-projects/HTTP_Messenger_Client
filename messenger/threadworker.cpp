#include "threadworker.h"
#include "jsondeserializer.h"
#include "Logger.h"

ThreadWorker::ThreadWorker(MainWindow* mW)
    :QObject(nullptr)
{
    mainWindow = mW;
    updaterThread = new M_Thread(mainWindow, this);
    connect(mainWindow, SIGNAL(start()), this, SLOT(StartThread()));
}

void ThreadWorker::StartThread()
{
    updaterThread->start();
}

ThreadWorker::~ThreadWorker()
{
    updaterThread->exit(0);
    delete updaterThread;
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
        QThread::sleep(2);
        LOG_DEBUG("Thread working");
    }
}
