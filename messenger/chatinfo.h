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

signals:
    void closing();

private slots:
    void closeEvent(QCloseEvent * e) override;

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
