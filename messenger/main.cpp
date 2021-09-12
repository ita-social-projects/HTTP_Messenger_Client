#include <QApplication>
#include "userinterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserInterface ui;
    return a.exec();
}
