#include "emoji.h"
#include "ui_emoji.h"

Emoji::Emoji(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emoji)
{
    ui->setupUi(this);
    this->setWindowTitle("Emoji");
}

Emoji::~Emoji()
{
    delete ui;
}

void Emoji::on_emoji_list_itemClicked(QTableWidgetItem *item)
{
    emit emojiSelected(item->text());
}

void Emoji::closeEvent(QCloseEvent * e)
{
    emit closing();
}

