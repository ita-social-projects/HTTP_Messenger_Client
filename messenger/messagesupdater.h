#pragma once
#ifndef MESSAGESUPDATER_H
#define MESSAGESUPDATER_H

#include <QObject>
#include "requestmanager.h"
#include "mainwindow.h"
class M_Thread;
class MessagesUpdater :  public QObject
{
    Q_OBJECT
private:
    MainWindow* mainWindow;
    QThread qthread;
    M_Thread* mt;

public:
    void StartThread();
    explicit MessagesUpdater(MainWindow&);
};

class M_Thread: public QThread
{
    Q_OBJECT
public:
    MainWindow* mainWindow;
    MessagesUpdater* messagesUpdater;
    explicit M_Thread(MainWindow*, MessagesUpdater*);
    void run();

private:
signals:
    void CheckNewMessagesSig();
};

#endif // MESSAGESUPDATER_H
