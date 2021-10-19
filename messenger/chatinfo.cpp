#include "chatinfo.h"
#include "ui_chatinfo.h"

ChatInfo::ChatInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatInfo)
{
    this->setWindowTitle("Chat Information");
    ui->setupUi(this);
}

ChatInfo::~ChatInfo()
{
    delete ui;
}
