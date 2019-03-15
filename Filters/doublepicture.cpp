#include "doublepicture.h"

#include <qDebug>

DoublePicture::DoublePicture(QObject *parent)
    : Filter(parent)
{

}

void DoublePicture::apply( RawImage *inputImage_ )
{
    inputImage = inputImage_;
    QImage oldImage = inputImage->getImage()->copy();
    RawImage oldRawImage(&oldImage);

    int newWidth = oldImage.width()/2;
    int newHeight = oldImage.height()/2;

    QPoint start = QPoint( newWidth / 2,
                           newHeight / 2 );
    QPoint end = QPoint( start.x() + newWidth,
                         start.y() + newHeight );

    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            inputImage->setPixel(i,j,qRgb(255,255,255));
        }
    }

    for (int j = start.y(); j < end.y(); j++)
    {
        for (int i = start.x(); i < end.x(); i++)
        {
            inputImage->setPixel((i - (newWidth/2)) * 2,
                                 (j - (newHeight/2)) * 2,
                                 oldRawImage.getPixel(i,j));
        }
    }

    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            if ( (i % 2 || j % 2))
            {
                countEmptyPixel(QPoint(i,j));
            }
        }
    }
}

bool DoublePicture::checkPoint(QSize size, QPoint point)
{
    bool result = true;

    result = result && point.x() >= 0 && point.y() >= 0;
    result = result && point.x() < size.width() &&
             point.y() < size.height();

    result = result && !(point.x() % 2) && !(point.y() % 2);

    return result;
}

void DoublePicture::processEmptyPoint( const QPoint &currentCoord )
{
    if ( checkPoint(inputImage->getImage()->size(), currentCoord) )
    {
        pixelsAmount++;
        QColor color = inputImage->getPixel(currentCoord.x(), currentCoord.y());
        red_av += color.red();
        green_av += color.green();
        blue_av += color.blue();
    }
}

void DoublePicture::countEmptyPixel(QPoint pixelCoord)
{
    red_av = 0;
    green_av = 0;
    blue_av = 0;
    pixelsAmount = 0;

    QPoint currentCoord(pixelCoord.x() - 1,pixelCoord.y() - 1);
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x());
    currentCoord.setY(pixelCoord.y() - 1);
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x() + 1);
    currentCoord.setY(pixelCoord.y());
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x() + 1);
    currentCoord.setY(pixelCoord.y() + 1);
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x());
    currentCoord.setY(pixelCoord.y() + 1);
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x() - 1 );
    currentCoord.setY(pixelCoord.y() + 1);
    processEmptyPoint(currentCoord);

    currentCoord.setX(pixelCoord.x() - 1);
    currentCoord.setY(pixelCoord.y());
    processEmptyPoint(currentCoord);

    red_av /= pixelsAmount;
    green_av /= pixelsAmount;
    blue_av /= pixelsAmount;
    inputImage->setPixel(pixelCoord.x(),
                         pixelCoord.y(),
                         qRgb(red_av, green_av, blue_av));
}
