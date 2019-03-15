#include "turningfilter.h"

TurningFilter::TurningFilter(QObject *parent, int angle) : Filter(parent),
                                                           angle(angle)
{

}

void TurningFilter::apply( RawImage *inputImage )
{
    QImage newImage = inputImage->getImage()->copy();
    RawImage *result = new RawImage(&newImage);


    double radianAngle = angle / 180.0 * M_PI;
    double sin = std::sin(radianAngle);
    double cos = std::cos(radianAngle);
    int centerX = inputImage->getImage()->width() / 2;
    int centerY = inputImage->getImage()->height() / 2;
    int height = inputImage->getImage()->height();
    int width = inputImage->getImage()->width();

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            result->setPixel(i,j,qRgb(255,255,255));
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int x = std::round(cos * (i - centerX) -
                               sin * (j - centerY) + centerX);

            int y = std::round(sin * (i - centerX) +
                               cos * (j - centerY) + centerY);
            if ( x >= 0 && y >= 0 && x < width && y < height )
            {
                result->setPixel(i,j,inputImage->getPixel(x,y));
            }
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            inputImage->setPixel(i,j, result->getPixel(i,j));
        }
    }

    delete result;
}
