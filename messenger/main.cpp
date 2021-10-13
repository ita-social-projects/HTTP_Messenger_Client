#include <QApplication>
#include "windowmanager.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    SET_LOGS_FILE("logs.txt");
    SHOW_LOGS_IN_CONSOLE(true);
    LOG_DEBUG("QApplication running");
    QApplication a(argc, argv);
    WindowManager ui;
    return a.exec();
}
