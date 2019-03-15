#include "gammafilter.h"

GammaFilter::GammaFilter(QObject *parent, float gamma) : Filter(parent), gamma(1.0/gamma)
{

}

void GammaFilter::apply(RawImage *inputImage)
{
    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            QColor color = inputImage->getPixel(i,j);
            inputImage->setPixel(i,j, qRgb(pow(color.redF(),   gamma) * 255,
                                           pow(color.greenF(), gamma) * 255,
                                           pow(color.blueF(),  gamma) * 255));
        }
    }
}
