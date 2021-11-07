#include "imagemanager.h"
#include <QFileDialog>
#include <QJsonObject>
#include <QPainter>

ImageManager::ImageManager()
{

}

const QPixmap ImageManager::uploadRoundedImage(QWidget* widget)
{
    return roundImage(uploadPhoto(widget));
}

const QPixmap ImageManager::uploadPhoto(QWidget* widget)
{
    QString fileName = QFileDialog::getOpenFileName(widget,"Open the file: "," ","PNG(*.png)");
    QFile file(fileName);
    QJsonObject obj;
    QPixmap p;
    QImage img;
    QJsonValue val;
    if(file.open( QIODevice::ReadOnly ) )
    {
        const QByteArray bytes = file.readAll();

        img = QImage::fromData(bytes);
        p.loadFromData(bytes, "PNG");
    }
    file.close();
    return p;
}

const QPixmap ImageManager::roundImage(const QPixmap &p)
{
    int radius = 50;
    QPixmap pixMap = p.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(),radius,radius);
    QPixmap pix = p.scaled(size);
    pix.setMask(mask);
    return pix;
}


