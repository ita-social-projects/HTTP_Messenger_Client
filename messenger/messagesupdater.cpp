#include "messagesupdater.h"

#include "JsonDeserializer.h"
#include "Logger.h"

MessagesUpdater::MessagesUpdater(MainWindow& mW)
    :QObject(nullptr)
{
    mainWindow = &mW;
    mt = new M_Thread(mainWindow, this);
}

void MessagesUpdater::StartThread()
{
    mt->start();
}

M_Thread::M_Thread(MainWindow* mW, MessagesUpdater* mU)
{
    mainWindow = mW;
    messagesUpdater = mU;
    connect(this, &M_Thread::doReq, mainWindow, &MainWindow::doRequdest);
}
void M_Thread::run()
{
    while (true)
    {

        if (mainWindow->currentChat.getId() == 0)
        {
            LOG_DEBUG("Doing update");
            continue;
        }
        emit doReq();
        QThread::sleep(1);
        LOG_DEBUG("Messages Update");
    }
}
