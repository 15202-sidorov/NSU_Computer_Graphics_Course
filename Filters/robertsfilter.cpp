#include "robertsfilter.h"

RobertsFilter::RobertsFilter(QObject *parent) : Filter(parent)
{

}

void RobertsFilter::checkColor( int &color )
{
    if ( color > 255 )
    {
        color = 255;
    }

    if ( color < 0 )
    {
        color = 0;
    }
}

void RobertsFilter::apply( RawImage *inputImage )
{
    GrayScaleColor *grayFilter = new GrayScaleColor(0);
    grayFilter->apply(inputImage);
    delete grayFilter;

    for (int j = 0; j < inputImage->getImage()->height() - 1; j++)
    {
        for (int i = 0; i < inputImage->getImage()->width() - 1; i++)
        {
            QColor bottomRight = inputImage->getPixel(i+1, j+1);
            QColor right = inputImage->getPixel(i+1, j);
            QColor bottom = inputImage->getPixel(i, j+1);
            QColor current = inputImage->getPixel(i,j);

            int Gx_red = bottomRight.red() - current.red();
            int Gy_red = right.red() - bottom.red();
            int Gx_green = bottomRight.green() - current.green();
            int Gy_green = right.green() - bottom.green();
            int Gx_blue = bottomRight.blue() - current.blue();
            int Gy_blue = right.blue() - bottom.blue();

            int result_red = sqrt(Gx_red * Gx_red + Gy_red * Gy_red);
            int result_green = sqrt(Gx_green * Gx_green + Gy_green * Gy_green);
            int result_blue = sqrt(Gx_blue * Gx_blue+ Gy_blue * Gy_blue);

            checkColor(result_red);
            checkColor(result_green);
            checkColor(result_blue);

            inputImage->setPixel(i,j, qRgb(result_red, result_green, result_blue));

        }
    }
}
