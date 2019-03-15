#include "ordereddither.h"

#include <QDebug>

const int OrderedDither::BATER[8][8] =
                    {
                            {0, 48, 12, 60, 3, 51, 15, 63},
                            {32, 16, 44, 28, 35, 19, 47, 31},
                            {8, 56, 4, 52, 11, 59, 7, 55},
                            {40, 24, 36, 20, 43, 27, 39, 23},
                            {2, 50, 14, 62, 1, 49, 13, 61},
                            {34, 18, 46, 30, 33, 17, 45, 29},
                            {10, 58, 6, 54, 9, 57, 5, 53},
                            {42, 26, 38, 22, 41, 25, 37, 21}
                    };

OrderedDither::OrderedDither(QObject *parent) : Filter(parent)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            BAYER[i][j] = BATER[i][j] * 4;
        }
    }

    for (int i = 8; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            BAYER[i][j] = BATER[i % 8][j] * 4 + 2;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 8; j < 16; j++)
        {
            BAYER[i][j] = BATER[i][j % 8] * 4 + 3;
        }
    }

    for (int i = 8; i < 16; i++)
    {
        for (int j = 8; j < 16; j++)
        {
            BAYER[i][j] = BATER[i % 8][j % 8] * 4 + 1;
        }
    }

}


void OrderedDither::apply( RawImage *inputImage )
{
    int newRed = 0;
    int newGreen = 0;
    int newBlue = 0;

    for (int j = 0; j < inputImage->getImage()->height(); j++)
    {
        for (int i = 0; i < inputImage->getImage()->width(); i++)
        {
            QColor color = inputImage->getPixel(i,j);
            if ( color.red() > BAYER[i % 16][j % 16] )
            {
                newRed = 255;
            }
            else
            {
                newRed = 0;
            }

            if ( color.blue() > BAYER[i % 8][j % 8] )
            {
                newBlue = 255;
            }
            else
            {
                newBlue = 0;
            }

            if ( color.green() > BAYER[i % 8][j % 8] )
            {
                newGreen = 255;
            }
            else
            {
                newGreen = 0;
            }

            inputImage->setPixel(i,j,qRgb(newRed,
                                          newGreen,
                                          newBlue));

        }
    }
}
