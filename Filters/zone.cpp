#include "zone.h"

#include <QDebug>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(ZONE_SIZE_WIDTH, ZONE_SIZE_HEIGHT);
    qimage = QImage(size(), QImage::Format_ARGB32);
    image = new RawImage(&qimage);
    drawBorder(false);
}

void Zone::drawBorder(bool borderOnly)
{
    if ( !borderOnly )
    {
        for (int j = 0; j < ZONE_SIZE_HEIGHT; j++)
        {
            for (int i = 0; i < ZONE_SIZE_WIDTH; i++)
            {
                image->setPixel(i,j,DEFAULT_ZONE_COLOR);
            }
        }
    }


    for (int i = 1; i < ZONE_SIZE_WIDTH; i++)
    {
        image->setPixel(i,0,DEFAULT_BORDER_COLOR);
        image->setPixel(i,ZONE_SIZE_HEIGHT - 1, DEFAULT_BORDER_COLOR);
        if ( !(i % BORDER_PADDING) )
        {
            for (int j = i; j < BORDER_PADDING + 1; j++)
            {
                image->setPixel(j,0,DEFAULT_ZONE_COLOR);
                image->setPixel(j, ZONE_SIZE_HEIGHT - 1, DEFAULT_ZONE_COLOR);
            }

            i += BORDER_PADDING + 1;
        }

        if ( i >= ZONE_SIZE_WIDTH ) break;

    }

    for (int i = 1; i < ZONE_SIZE_HEIGHT; i++)
    {
        image->setPixel(0,i,DEFAULT_BORDER_COLOR);
        image->setPixel(ZONE_SIZE_WIDTH - 1, i, DEFAULT_BORDER_COLOR);
        if ( !(i % BORDER_PADDING) )
        {
            for (int j = i; j < BORDER_PADDING + 1; j++)
            {
                image->setPixel(0,j,DEFAULT_ZONE_COLOR);
                image->setPixel(ZONE_SIZE_WIDTH - 1, j, DEFAULT_ZONE_COLOR);
            }

            i += BORDER_PADDING + 1;
        }

        if ( i >= ZONE_SIZE_HEIGHT ) break;
    }
}

void Zone::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);
    painter.drawImage(0,0,*image->getImage());
}


Zone::~Zone()
{
    delete image;
}
