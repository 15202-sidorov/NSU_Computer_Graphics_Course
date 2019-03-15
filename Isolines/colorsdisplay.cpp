#include "colorsdisplay.h"

#include <QDebug>

ColorsDisplay::ColorsDisplay(QWidget *parent) : QWidget(parent)
{
    setFixedSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y);
    for (int j = 0; j < DEFAULT_SIZE_Y; j++)
    {
        for (int i = 0; i < DEFAULT_SIZE_X; i++)
        {
            image.setPixel(i,j,DEFAULT_COLOR);
        }
    }
}

void ColorsDisplay::paintVertical( const QRgb &color, int x )
{
    for (int j = 0; j < size().height(); j++)
    {
        image.setPixel(x,j,color);
    }
}

void ColorsDisplay::addColor( const QRgb &newColor )
{
    colorsAmount++;
    colors.push_back(newColor);
    paintNormal();
}

void ColorsDisplay::paintNormal()
{
    int width = size().width()/colorsAmount;
    for (int color = 0; color < colorsAmount; color++)
    {
        for (int i = color * width; i < size().width(); i++)
        {
            paintVertical(colors[color], i);
        }
    }
}

int ColorsDisplay::interpoateColor(int color1, int color2,
                                   int color_index, int i,
                                   int width)
{
    int result = (color1 * ( (color_index+1)*width - i) / width) +
            (color2 * ( i - color_index * width)) / width;

    if ( result > 255 )
    {
        result = 255;
    }

    if ( result < 0 )
    {
        result = 0;
    }

    return result;
}

void ColorsDisplay::interpolate()
{
    int width = size().width() / (colorsAmount - 1);
    QColor currentColor;
    QColor color1;
    QColor color2;
    for (int color = 0; color < colorsAmount-1; color++)
    {
        for (int i = (color) * width; i < (color + 1) * width; i++)
        {
            color1 = colors[color];
            color2 = colors[color + 1];

            currentColor.setRed(interpoateColor(color1.red(), color2.red(),
                                                color, i, width));
            currentColor.setGreen(interpoateColor(color1.green(), color2.green(),
                                                  color, i,width));
            currentColor.setBlue(interpoateColor(color1.blue(), color2.blue(),
                                                 color, i,width));
            paintVertical(currentColor.rgb(), i);
        }
    }
}

void ColorsDisplay::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);
    painter.drawImage(0,0, *image.getImage());
}
