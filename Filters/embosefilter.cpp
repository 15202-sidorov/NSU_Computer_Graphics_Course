#include "embosefilter.h"

const int EmboseFilter::kernel[EmboseFilter::KERNEL_SIZE_X][EmboseFilter::KERNEL_SIZE_Y] =
                                        {{ 0,  1, 0},
                                         {-1,  0, 1},
                                         { 0, -1, 0}};

EmboseFilter::EmboseFilter(QObject *parent) : Filter(parent)
{

}

void EmboseFilter::checkColor( float &color )
{
     if ( color > 255 )
     {
        color = 255;
     }
     else if ( color < 0 )
     {
        color = 0;
     }
}


void EmboseFilter::apply( RawImage * inputImage )
{
    int width = inputImage->getImage()->width();
    int height = inputImage->getImage()->height();

    QVector<QRgb> temp(width * height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float redSum   = 0;
            float greenSum = 0;
            float blueSum  = 0;
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

                    QColor color(inputImage->getPixel( i + (x - 1), j + (y - 1)));
                    redSum   += kernel[x][y] * color.red();
                    greenSum += kernel[x][y] * color.green();
                    blueSum  += kernel[x][y] * color.blue();
                }
            }

            redSum   += 128;
            greenSum += 128;
            blueSum  += 128;

            checkColor(redSum);
            checkColor(greenSum);
            checkColor(blueSum);

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
