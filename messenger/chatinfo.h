#ifndef CHATINFO_H
#define CHATINFO_H

#include <QDialog>

namespace Ui {
class ChatInfo;
}

class ChatInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = nullptr);
    ~ChatInfo();

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
