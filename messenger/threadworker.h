#pragma once
#ifndef MESSAGESUPDATER_H
#define MESSAGESUPDATER_H

#include <QObject>
#include "requestmanager.h"
#include "mainwindow.h"
class M_Thread;
class ThreadWorker :  public QObject
{
    Q_OBJECT
private:
    MainWindow* mainWindow;
    M_Thread* updaterThread;

public:
    void StartThread();
    ~ThreadWorker();
    explicit ThreadWorker(MainWindow*);
};

class M_Thread: public QThread
{
    Q_OBJECT
public:
    MainWindow* mainWindow;
    ThreadWorker* messagesUpdater;
    explicit M_Thread(MainWindow*, ThreadWorker*);
    void run();

signals:
    void SendRequests();
};

#endif // MESSAGESUPDATER_H
