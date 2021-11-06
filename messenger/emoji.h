#ifndef EMOJI_H
#define EMOJI_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class Emoji;
}

class Emoji : public QDialog
{
    Q_OBJECT

public:
    explicit Emoji(QWidget *parent = nullptr);
    ~Emoji();

signals:
    void emojiSelected(QString);
    void closing();

private slots:
    void on_emoji_list_itemClicked(QTableWidgetItem *item);
    void closeEvent(QCloseEvent * e) override;

private:
    Ui::Emoji *ui;
};

#endif // EMOJI_H
