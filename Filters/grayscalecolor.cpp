#include "grayscalecolor.h"

GrayScaleColor::GrayScaleColor(QObject *parent): Filter(parent)
{

}

void GrayScaleColor::checkColor(float *color)
{
    if ( *color > 255 )
    {
        *color = 255;
    }
    else if ( *color < 0 )
    {
        *color = 0;
    }
}

void GrayScaleColor::apply( RawImage *inputImage )
{

    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            QColor pixel = inputImage->getPixel(i,j);
            float grayColor = 0.299f * pixel.red() +
                              0.587f * pixel.green() +
                              0.144f * pixel.blue();
            checkColor(&grayColor);
            inputImage->setPixel(i,j,
                                 qRgb(grayColor,
                                      grayColor,
                                      grayColor));
        }
    }
}
