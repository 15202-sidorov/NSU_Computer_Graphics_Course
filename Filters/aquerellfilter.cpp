#include "aquerellfilter.h"

const float AquerellFilter::kernel[AquerellFilter::KERNEL_WIDTH][AquerellFilter::KERNEL_HEIGHT]
    = {
        {-0.75, -0.75, -0.75},
        {-0.75,     7, -0.75},
        {-0.75, -0.75, -0.75}
       };

AquerellFilter::AquerellFilter(QObject *parent) : Filter(parent)
{

}

void AquerellFilter::apply( RawImage *inputImage )
{
    QImage originalImage = inputImage->getImage()->copy();
    RawImage *median = new RawImage(&originalImage);

    for (int j = 3; j < originalImage.height() - 3; j++)
    {
        for (int i = 3; i < originalImage.width() - 3; i++)
        {
            calculateColor(inputImage,median,i,j);
        }
    }

    for (int j = 1; j < originalImage.height() - 1; j++)
    {
        for (int i = 1; i < originalImage.width() - 1; i++)
        {
            calculateContur(inputImage,median,i,j);
        }
    }

    delete median;
}

void AquerellFilter::calculateColor( RawImage *inputImage,
                                     RawImage *median,
                                     int x, int y)
{
    std::vector<int> m_red(25);
    std::vector<int> m_green(25);
    std::vector<int> m_blue(25);
    QColor color(0,0,0);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            color = (QColor)inputImage->getPixel(x + (i - 3),y + (j - 3));
            m_red[i * 3 + j] = color.red();
            m_green[i * 3 + j] = color.green();
            m_blue[i * 3 + j] = color.blue();
        }
    }

    std::sort(m_red.begin(), m_red.end());
    std::sort(m_green.begin(), m_green.end());
    std::sort(m_blue.begin(), m_blue.end());

    int result_red =  m_red[13];
    int result_green = m_green[13];
    int result_blue = m_blue[13];

    median->setPixel(x, y, qRgb(result_red, result_green, result_blue));
}

void AquerellFilter::checkColor( int &color )
{
    if ( color  < 0 )
    {
        color = 0;
    }

    if ( color > 255 )
    {
        color = 255;
    }
}

void AquerellFilter::calculateContur( RawImage *inputImage,
                                      RawImage *median,
                                      int x, int y)
{
    int redSum   = 0;
    int greenSum = 0;
    int blueSum  = 0;

    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
           redSum   += kernel[i - (x - 1)][j - (y - 1)] * ((QColor)median->getPixel(i,j)).red();
           greenSum += kernel[i - (x - 1)][j - (y - 1)] * ((QColor)median->getPixel(i,j)).green();
           blueSum  += kernel[i - (x - 1)][j - (y - 1)] * ((QColor)median->getPixel(i,j)).blue();
        }
    }

    checkColor(redSum);
    checkColor(greenSum);
    checkColor(blueSum);

    inputImage->setPixel(x,y,qRgb(redSum, greenSum, blueSum));
}
