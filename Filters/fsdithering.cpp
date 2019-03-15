#include "fsdithering.h"

FSDithering::FSDithering(QWidget *parent) : Filter(parent)
{

}

void FSDithering::apply( RawImage *inputImage )
{
    int width = inputImage->getImage()->width();
    int height = inputImage->getImage()->height();
    QVector<float> red_colors(width * height);
    QVector<float> green_colors(width * height);
    QVector<float> blue_colors(width * height);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            QColor color(inputImage->getPixel(i,j));
            red_colors[j * width + i] = color.redF();
            green_colors[j * width + i] = color.greenF();
            blue_colors[j * width + i] = color.blueF();
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float nRed = round(red_colors[j * width + i] * redN ) / redN;
            float nGreen = round(green_colors[j * width + i] * greenN ) / greenN;
            float nBlue = round(blue_colors[j * width + i] * blueN ) / blueN;

            inputImage->setPixel(i,j,qRgb(nRed * 255, nGreen * 255, nBlue * 255));
            float redErr = red_colors[j * width + i] - nRed;
            float greenErr = green_colors[j * width + i] - nGreen;
            float blueErr = blue_colors[j + width + i] - nBlue;

            int currentIndex = j * width + i + 1;
            if ( i + 1 < width )
            {
                red_colors[currentIndex] += redErr * RIGHT_COEFFICIENT;
                green_colors[currentIndex] += greenErr * RIGHT_COEFFICIENT;
                blue_colors[currentIndex] += blueErr * RIGHT_COEFFICIENT;
            }

            if ( j > 0 )
            {
                currentIndex = (j - 1) * width + i;
                red_colors[currentIndex] += redErr * BOTTOM_COEFFICIENT;
                green_colors[currentIndex] += greenErr * BOTTOM_COEFFICIENT;
                blue_colors[currentIndex] += blueErr * BOTTOM_COEFFICIENT;
            }

            if ( j > 0 && i > 0 )
            {
                currentIndex = (j - 1) * width + i - 1;
                red_colors[currentIndex] += redErr * BOTTOM_LEFT_COEFFICIENT;
                green_colors[currentIndex] += greenErr * BOTTOM_LEFT_COEFFICIENT;
                blue_colors[currentIndex] += blueErr * BOTTOM_LEFT_COEFFICIENT;
            }
        }
    }

}
