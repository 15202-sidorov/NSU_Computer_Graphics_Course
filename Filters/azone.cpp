#include "azone.h"

#include <QDebug>

AZone::AZone(QWidget *parent) : Zone(parent)
{
    resultSize.setWidth(WINDOW_WIDTH);
    resultSize.setHeight(WINDOW_HEIGHT);
    blockSignals(true);
}

void AZone::setImage( QImage inputImage )
{
    originalImage = inputImage;
    QImage resultImage(size(), QImage::Format_ARGB32);
    RawImage temp(&resultImage);
    RawImage rawInputImage(&inputImage);

    originalSize = inputImage.size();

    for (int j = 0; j < ZONE_SIZE_HEIGHT; j++)
    {
        for( int i = 0; i < ZONE_SIZE_WIDTH; i++)
        {
            temp.setPixel(i,j,DEFAULT_ZONE_COLOR);
        }
    }

    if ( inputImage.width() >= inputImage.height() )
    {
        resultSize.setWidth(size().width() - 2);
        resultSize.setHeight(inputImage.height() * resultSize.width() / inputImage.width());
    }
    else
    {
        resultSize.setHeight(size().height() - 2);
        resultSize.setWidth(inputImage.width() * resultSize.height() / inputImage.height());
    }

    inputImage = rawInputImage.getImage()->scaled(resultSize);
    rawInputImage.setImage(&inputImage);

    for (int j = 0; j < resultSize.height(); j++)
    {
        for (int i = 0; i < resultSize.width(); i++)
        {
            temp.setPixel(i + 1,j + 1,rawInputImage.getPixel(i,j));
        }
    }

    qimage = *temp.getImage();
    image->setImage(&qimage);
    drawBorder(true);
    countWindowSize();
    blockSignals(false);
}

void AZone::drawWindow( QPoint center )
{
    QPoint start(center.x() - (windowSize.width() / 2), center.y() - (windowSize.height() / 2));
    QPoint end(center.x() + (windowSize.width() / 2), center.y() + (windowSize.height() / 2) );

    checkBorders(start, end);

    int dashPadding = (end.y() - start.y()) / DASH_AMOUNT;

    for (int j = start.y(); j < end.y(); j++)
    {
        if ( !(j % dashPadding) )
        {
            j += dashPadding + 1;
        }

        if ( j > end.y() )
        {
            break;
        }
        QColor currentColorStart = image->getPixel(start.x(),j);
        QColor currentColorEnd = image->getPixel(end.x(), j);
        image->setPixel(start.x(), j, qRgb(255 - currentColorStart.red(),
                                           255 - currentColorStart.green(),
                                           255 - currentColorStart.blue()));
        image->setPixel(end.x(), j, qRgb(255 - currentColorEnd.red(),
                                         255 - currentColorEnd.green(),
                                         255 - currentColorEnd.blue()));
    }

    for(int i = start.x(); i < end.x(); i++)
    {
        if ( !(i % dashPadding) )
        {
            i += dashPadding + 1;
        }

        if ( i > end.x() )
        {
            break;
        }
        QColor currentColorStart = image->getPixel(i,start.y());
        QColor currentColorEnd = image->getPixel(i,end.y());

        image->setPixel(i, start.y(), qRgb(255 - currentColorStart.red(),
                                           255 - currentColorStart.green(),
                                           255 - currentColorStart.blue()));
        image->setPixel(i, end.y(),   qRgb(255 - currentColorEnd.red(),
                                           255 - currentColorEnd.green(),
                                           255 - currentColorEnd.blue()));
    }

    // x / original_size = center / result_size
    QPoint originalCenter(center.x() * originalSize.width() / resultSize.width(),
                          center.y() * originalSize.height() / resultSize.height());

    start.setX(originalCenter.x() - (WINDOW_WIDTH/2));
    start.setY(originalCenter.y() - (WINDOW_HEIGHT/2));

    if ( start.x() < 0 )
    {
        start.setX(0);
    }

    if ( start.y() < 0 )
    {
        start.setY(0);
    }

    if ( start.x() + WINDOW_WIDTH >= originalSize.width() )
    {
        start.setX(start.x() - (start.x() + WINDOW_WIDTH - originalSize.width()));
    }

    if ( start.y() + WINDOW_HEIGHT >= originalSize.height() )
    {
        start.setY( start.y() - (start.y() + WINDOW_HEIGHT - originalSize.height()));
    }

    windowRect.setX(start.x());
    windowRect.setY(start.y());
    windowRect.setSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    emit newImage(originalImage.copy(windowRect)) ;
}

void AZone::checkBorders( QPoint &start, QPoint &end )
{
    int dy = 0;
    int dx = 0;

    if ( start.x() < 0 )
    {
        dx = -1 * start.x();
        start.setX(0);
        end.setX(end.x() + dx);
    }

    if ( start.y() < 0 )
    {
        dy = -1 * start.y();
        start.setY(0);
        end.setY(end.y() + dy);
    }

    if ( end.x() >= resultSize.width() )
    {
        dx = resultSize.width() - end.x();
        end.setX(resultSize.width() - 1);
        start.setX(start.x() + dx);
    }

    if ( end.y() >= resultSize.height() )
    {
        dy = resultSize.height() - end.y();
        end.setY(resultSize.height() - 1);
        start.setY(start.y() + dy);
    }
}

void AZone::countWindowSize()
{
    // 350 / originalSize = x / resultSize
    windowSize.setWidth(resultSize.width() * WINDOW_WIDTH / originalSize.width());
    windowSize.setHeight(resultSize.height() * WINDOW_HEIGHT / originalSize.height());
}


void AZone::mousePressEvent( QMouseEvent *mouseEvent )
{
    if ( signalsBlocked() )
    {
        return;
    }

    drawWindow(mouseEvent->pos());
    repaint();
}

void AZone::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if ( signalsBlocked() )
    {
        return;
    }
    setImage(originalImage);
    repaint();
}

void AZone::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if ( signalsBlocked() )
    {
        return;
    }
    setImage(originalImage);
    drawWindow(mouseEvent->pos());
    repaint();
}
