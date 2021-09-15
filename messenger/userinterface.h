#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QObject>
#include <QWidget>

class UserInterface : public QObject
{
    Q_OBJECT
public:
    explicit UserInterface(QObject *parent = nullptr);
    ~UserInterface();
private slots:
    void open_LoginWindow();
    void open_SignupWindow();
    void open_MainWindow();
private:
    QWidget *current_window;
};

#endif // USERINTERFACE_H
