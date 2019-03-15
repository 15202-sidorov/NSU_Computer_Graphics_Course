#include "sobeloperator.h"

const int SobelOperator::kernel_x[SobelOperator::KERNEL_SIZE_X][SobelOperator::KERNEL_SIZE_Y] =
    {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };

const int SobelOperator::kernel_y[SobelOperator::KERNEL_SIZE_X][SobelOperator::KERNEL_SIZE_Y] =
    {
        {1,   2,  1},
        {0,   0,  0},
        {-1, -2, -1}
    };

SobelOperator::SobelOperator(QObject *parent) : Filter(parent)
{

}

void SobelOperator::checkColor( float *color_ptr )
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

void SobelOperator::apply( RawImage *inputImage )
{
    GrayScaleColor *grayFilter = new GrayScaleColor(0);
    grayFilter->apply(inputImage);
    delete grayFilter;

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
                    redSum   += kernel_x[x][y] * color.red();
                    greenSum += kernel_x[x][y] * color.green();
                    blueSum  += kernel_x[x][y] * color.blue();
                }
            }

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
                    redSum   += kernel_y[x][y] * color.red();
                    greenSum += kernel_y[x][y] * color.green();
                    blueSum  += kernel_y[x][y] * color.blue();
                }
            }

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
