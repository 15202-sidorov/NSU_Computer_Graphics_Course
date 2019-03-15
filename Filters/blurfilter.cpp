#include "blurfilter.h"

const int BlurFilter::kernel[BlurFilter::KERNEL_SIZE_X][BlurFilter::KERNEL_SIZE_Y] =
    {
      {0, 1, 0},
      {1, 2, 1},
      {0, 1, 0}
    };

BlurFilter::BlurFilter(QObject *parent) : Filter(parent)
{

}

void BlurFilter::checkColor( int *color_ptr )
{
    if ( *color_ptr > 255 )
    {
        *color_ptr = 255;
    }
    else if ( *color_ptr < 0 )
    {
        *color_ptr = 0;
    }
}

void BlurFilter::apply( RawImage *inputImage )
{
    int width = inputImage->getImage()->width();
    int height = inputImage->getImage()->height();
    QColor color;

    QRgb  temp[width * height];
    int redSum   = 0;
    int greenSum = 0;
    int blueSum  = 0;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            redSum = 0;
            greenSum = 0;
            blueSum = 0;
            for (int y = 0; y < KERNEL_SIZE_Y; y++)
            {
                for (int x = 0; x < KERNEL_SIZE_X; x++)
                {
                    if (i + (x - 1) < 0 ||
                        width <= i + (x - 1) ||
                        j + (y- 1) < 0 ||
                        height <= j + (y - 1))
                    {
                        continue;
                    }

                    color.setRgb(inputImage->getPixel( i + (x - 1), j + (y - 1)));
                    redSum   += kernel[x][y] * color.red();
                    greenSum += kernel[x][y] * color.green();
                    blueSum  += kernel[x][y] * color.blue();
                }
            }

            redSum   *= MATRIX_COEFFICIENT;
            greenSum *= MATRIX_COEFFICIENT;
            blueSum  *= MATRIX_COEFFICIENT;

            checkColor(&redSum);
            checkColor(&greenSum);
            checkColor(&blueSum);

            temp[j * width + i] = qRgb(redSum, greenSum, blueSum);
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            inputImage->setPixel(i,j,temp[j * width + i]);
        }
    }
}
