#include "negativecolor.h"

NegativeColor::NegativeColor(QObject *parent): Filter(parent)
{

}

void NegativeColor::apply( RawImage *inputImage )
{
    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            QColor pixel = inputImage->getPixel(i,j);
            inputImage->setPixel(i,j, qRgb(255 - pixel.red(),
                                           255 - pixel.green(),
                                           255 - pixel.blue()));
        }
    }
}

