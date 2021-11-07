#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <QPixmap>

class ImageManager
{
public:
    ImageManager();
    const QPixmap uploadRoundedImage(QWidget* widget);
private:
    const QPixmap roundImage(const QPixmap &pix);
    const QPixmap uploadPhoto(QWidget* widget);
};

#endif // IMAGEMANAGER_H
