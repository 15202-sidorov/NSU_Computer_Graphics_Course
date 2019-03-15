#ifndef RAWIMAGE_H
#define RAWIMAGE_H

#include <QWidget>
#include <memory.h>
#include <iostream>

class RawImage
{

public:
    inline RawImage(QImage * parent)
    {
        parentImage = parent;
        bytesPerLine = parentImage->bytesPerLine();
        data = parentImage->bits();
    }

    inline RawImage()
    {

    }

    inline void setImage(QImage * parent)
    {
        parentImage = parent;
        bytesPerLine = parentImage->bytesPerLine();
        data = parentImage->bits();
    }

    inline void setPixel(int x, int y, QRgb color)
    {
        if (( x < parentImage->size().width() && y < parentImage->size().height() ) &&
            ( x >= 0 ) && ( y >= 0 ))
        {
            setPixel_(x,y,color);
        }

        return;
    }

    inline QRgb &getPixel(int x, int y)
    {
        if (( x < parentImage->size().width() && y < parentImage->size().height() ) &&
            ( x >= 0 ) && ( y >= 0 ))
        {
            return getPixel_(x,y);
        }

        return *(QRgb *)(data);
    }

    inline QImage *getImage()
    {
        return parentImage;
    }

    inline ~RawImage() {
        delete parentImage;
    }

private:
    inline void setPixel_(int x, int y, QRgb color)
    {
        uchar *targetPixelPtr = data;
        targetPixelPtr += bytesPerLine * y + x * 4;
        QRgb *rgbPtr = (QRgb *)targetPixelPtr;
        *rgbPtr = color;
    }

    inline QRgb &getPixel_(int x, int y)
    {
        return *(QRgb *)(data + bytesPerLine * y + x * 4);
    }

    QImage *parentImage;
    uchar *data;
    int bytesPerLine;
};

#endif // RAWIMAGE_H
