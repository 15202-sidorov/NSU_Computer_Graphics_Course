#include "drawarea.h"

#include <qDebug>

Drawarea::Drawarea(QWidget *parent,
                   ColorsDisplay *inputDisplay,
                   Function *inputFunction) :
    QWidget(parent),
    display(inputDisplay),
    function(inputFunction)
{
    setFixedSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y);
    for (int j = 0; j < DEFAULT_SIZE_Y; j++)
    {
        for (int i = 0; i < DEFAULT_SIZE_X; i++)
        {
            image.setPixel(i,j,DEFAULT_COLOR);
        }
    }
    setMouseTracking(true);
}

void Drawarea::biliniarInterpolation( int i, int j )
{
    float BWidth = function->getMaxX() - function->getMinX();
    float BHeight = function->getMaxY() - function->getMinY();
    int colorsAmount = display->getColorsAmount();
    float delta = (function->getFunctionMax() - function->getFunctionMin())/colorsAmount;
    float currentX = BWidth * i/( size().width() + function->getMinX() );
    float currentY =  BHeight * j/( size().height() + function->getMaxX() );

    float value = function->calculate(currentX, currentY);

    int pixel_needed = display->width() * (value - function->getFunctionMin()) / ( delta * colorsAmount );
    if ( pixel_needed >= display->width() )
    {
        pixel_needed = display->width() - 1;
    }
    image.setPixel(i,j, display->getPixel(pixel_needed));
}

void Drawarea::drawIsolines()
{
    QRgb currentColorRgb;
    int colorsAmount = display->getColorsAmount();
    float delta = (function->getFunctionMax() - function->getFunctionMin())/colorsAmount;


    for (int i = 0; i < size().width(); i++)
    {
        currentColorRgb = image.getPixel(i,0);
        for (int j = 0; j < size().height(); j++)
        {
            if ( currentColorRgb != image.getPixel(i,j) )
            {
                currentColorRgb = image.getPixel(i,j);
                image.setPixel(i,j,ISOLINE_COLOR);
            }
        }
    }

    for (int j = 0; j < size().height(); j++)
    {
        currentColorRgb = image.getPixel(0,j);
        for (int i = 0; i < size().width(); i++)
        {
            if ( currentColorRgb != image.getPixel(i,j) )
            {
                currentColorRgb = image.getPixel(i,j);
                image.setPixel(i,j,ISOLINE_COLOR);
            }
        }
    }

    for ( int i = 0; i < colorsAmount; i++ )
    {
        drawGridIsolines(function->getFunctionMin() + i * delta);
    }
}

QRgb Drawarea::defineColor( int i, int j )
{
    int colorsAmount = display->getColorsAmount();
    float BWidth = function->getMaxX() - function->getMinX();
    float BHeight = function->getMaxY() - function->getMinY();
    float delta = (function->getFunctionMax() - function->getFunctionMin())/colorsAmount;
    float currentX = BWidth * i/( size().width() + function->getMinX() );
    float currentY =  BHeight * j/( size().height() + function->getMaxX() );
    float value = function->calculate(currentX, currentY);

    for (int k = 0; k < colorsAmount; k++)
    {
        if ( k == 0 )
        {
            if ( value < function->getFunctionMin() + delta * (k + 1) )
            {
                return display->getColor(k);
            }
            continue;
        }

        if ( k == colorsAmount - 1 )
        {
            if (value >= function->getFunctionMin() + delta * k)
            {
                return display->getColor(k);
            }
            continue;
        }

        if (( value <=  function->getFunctionMin() + delta * (k + 1) )
                && ( value >= function->getFunctionMin() + delta * k ))
        {
            return display->getColor(k);
        }
    }

    return DEFAULT_COLOR;
}

void Drawarea::mouseMoveEvent( QMouseEvent *event )
{
    int i = event->x();
    int j = event->y();
    float BWidth = function->getMaxX() - function->getMinX();
    float BHeight = function->getMaxY() - function->getMinY();
    float currentX = BWidth * i/( size().width() + function->getMinX() );
    float currentY =  BHeight * j/( size().height() + function->getMaxX() );
    if ( currentX > function->getMaxX() || currentX < function->getMinX() ||
         currentY > function->getMaxY() || currentY < function->getMinY())
    {
        return;
    }
    float value = function->calculate(currentX, currentY);
    emit refreshFunctionValues(currentX, currentY, value);

    if ( event->buttons() == Qt::LeftButton )
    {
        mousePressEvent(event);
    }

}

void Drawarea::mousePressEvent( QMouseEvent *event )
{
    float delta = (function->getFunctionMax() - function->getFunctionMin())/display->getColorsAmount();
    float BWidth = function->getMaxX() - function->getMinX();
    float BHeight = function->getMaxY() - function->getMinY();
    float currentX = BWidth * event->x()/( size().width() + function->getMinX() );
    float currentY =  BHeight * event->y()/( size().height() + function->getMaxX() );
    float value = function->calculate(currentX, currentY);
    clearGrid();
    for ( int i = 0; i < display->getColorsAmount(); i++ )
    {
        drawGridIsolines(function->getFunctionMin() + i * delta);
    }

    drawGridIsolines(value);
    repaint();
}

void Drawarea::clearGrid()
{
    for (int i = 0; i < size().width(); i++)
    {
        for (int j = 0; j < size().height(); j++)
        {
            gridImage.setPixel(i,j,qRgba(0,0,0,0));
        }
    }
}

void Drawarea::drawFunction()
{
   QRgb resultPixel;
   display->paintNormal();
   for (int j = 0; j < size().height(); j++)
    {
        for (int i = 0; i < size().width(); i++)
        {
            resultPixel = defineColor(i,j);
            image.setPixel(i,j,resultPixel);
        }
    }
}

void Drawarea::drawGridHorizontalLine(int i)
{
    for (int j = 0; j < size().height(); j++)
    {
        image.setPixel(i,j,GRID_COLOR);
    }
}

void Drawarea::drawGridVerictalLine(int j)
{
    for (int i = 0; i < size().width(); i++)
    {
        image.setPixel(i,j,GRID_COLOR);
    }
}

void Drawarea::drawGrid()
{
    int deltaHeight = size().height() / GRID_M;
    int deltaWidth = size().width() / GRID_K;

    for (int i = 0; i <= size().width(); i += deltaWidth)
    {
        drawGridHorizontalLine(i);
    }

    for (int j = 0; j <= size().height(); j += deltaHeight)
    {
        drawGridVerictalLine(j);
    }
}

float Drawarea::defineIsoline( float f1, float f2,
                                float z, float dx )
{
    if ( !(((z < f1) && (z < f2)) ||
           ((z > f1) && (z > f2))) )
    {
        return dx * fabs(z - f1) / fabs(f2 - f1);
    }
    else
    {
        return -1;
    }
}

void Drawarea::drawLine( QPoint currentPoint,
                         QPoint newPoint )
{
    drawCircle(currentPoint);
    drawCircle(newPoint);
    QPoint prevPoint = currentPoint;
    currentPoint = newPoint;

    const int deltaX = abs(currentPoint.x() - prevPoint.x());
    const int deltaY = abs(currentPoint.y() - prevPoint.y());

    const int signX  = prevPoint.x() < currentPoint.x() ? 1 : -1;
    const int signY  = prevPoint.y() < currentPoint.y() ? 1 : -1;

    int error = deltaX - deltaY;
    gridImage.setPixel(prevPoint.x(), prevPoint.y(), GRID_COLOR);
    while ( currentPoint.x() != prevPoint.x() || currentPoint.y() != prevPoint.y() )
    {
        gridImage.setPixel(prevPoint.x(),       prevPoint.y() ,     GRID_COLOR);

        const int next_error = error * 2;
        if ( next_error > -deltaY )
        {
            error -= deltaY;
            prevPoint.setX(prevPoint.x() + signX);
        }

        if ( next_error < deltaX )
        {
            error += deltaX;
            prevPoint.setY(prevPoint.y() + signY);
        }
    }
}

void Drawarea::drawCircle( QPoint center )
{
    int x0 = center.x();
    int y0 = center.y();
    int x = CIRCLE_SIZE - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (CIRCLE_SIZE << 1);
    while (x >= y)
    {
        gridImage.setPixel(x0 + x, y0 + y,CIRCLE_COLOR);
        gridImage.setPixel(x0 + y, y0 + x,CIRCLE_COLOR);
        gridImage.setPixel(x0 - y, y0 + x,CIRCLE_COLOR);
        gridImage.setPixel(x0 - x, y0 + y,CIRCLE_COLOR);
        gridImage.setPixel(x0 - x, y0 - y,CIRCLE_COLOR);
        gridImage.setPixel(x0 - y, y0 - x,CIRCLE_COLOR);
        gridImage.setPixel(x0 + y, y0 - x,CIRCLE_COLOR);
        gridImage.setPixel(x0 + x, y0 - y,CIRCLE_COLOR);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (CIRCLE_SIZE << 1);
        }
    }
}

void Drawarea::drawGridIsolines( float z )
{
    float BWidth = function->getMaxX() - function->getMinX();
    float BHeight = function->getMaxY() - function->getMinY();
    int deltaHeight = size().height() / GRID_M;
    int deltaWidth = size().width() / GRID_K;
    float dx = BWidth / GRID_K;
    float dy = BHeight / GRID_M;

    float f1 = 0;
    float f2 = 0;
    float f3 = 0;
    float f4 = 0;
    float x = 0;

    QPoint point[4];
    int pointsAmount = 0;
    bool pointExists[4];

    for (int j = 0; j < GRID_M; j++)
    {
        for (int i = 0; i < GRID_K; i++)
        {
            f1 = function->calculate(i * dx, j * dy);
            f2 = function->calculate((i + 1) * dx, j * dy);
            f3 = function->calculate((i + 1)* dx, (j + 1) * dy);
            f4 = function->calculate(i * dx, (j + 1) * dy);

            for (int k = 0; k < 4; k++)
            {
                pointExists[k] = false;
            }

            x = defineIsoline(f1,f2,z,dx);
            if ( -1 != x )
            {
                point[0].setX(i * deltaWidth + (x * deltaWidth) / dx);
                point[0].setY(j * deltaHeight);
                pointExists[0] = true;
            }
            x = defineIsoline(f2,f3,z,dy);
            if ( -1 != x )
            {
                point[1].setX((i + 1) * deltaWidth);
                point[1].setY(j * deltaHeight + (x * deltaHeight) / dy);
                pointExists[1] = true;
            }
            x = defineIsoline(f3,f4,z,dx);
            if ( -1 != x )
            {
                point[2].setX((i + 1) * deltaWidth - (x * deltaWidth) / dx);
                point[2].setY((j + 1) * deltaHeight);
                pointExists[2] = true;
            }
            x = defineIsoline(f4,f1,z,dy);
            if ( -1 != x )
            {
                point[3].setX(i * deltaWidth);
                point[3].setY((j + 1) * deltaHeight - (x * deltaHeight) / dy);
                pointExists[3] = true;
            }

            pointsAmount = 0;
            for (int k = 0; k < 4; k++)
            {
                pointsAmount += pointExists[k];
            }

            int index1 = -1;
            int index2 = -1;

            if ( pointsAmount == 2 )
            {

                for (int k = 0; k < 4; k++)
                {
                    if ( pointExists[k] )
                    {
                        if ( -1 == index1 ) index1 = k;
                        else index2 = k;
                    }
                }

                drawLine(point[index1],point[index2]);
            }
            else if ( pointsAmount == 4 )
            {
                if ( function->calculate(i * dx + dx/2, j * dy + dy/2) < z )
                {
                    drawLine(point[0], point[3]);
                    drawLine(point[1], point[2]);
                }
                else
                {
                    drawLine(point[0], point[1]);
                    drawLine(point[2], point[3]);
                }
            }
        }
    }
}

void Drawarea::interpolate()
{
    display->interpolate();
    for (int j = 0; j < size().height(); j++)
    {
        for (int i = 0; i < size().width(); i++)
        {
            if ( !(image.getPixel(i,j) == ISOLINE_COLOR) &&
                 !(image.getPixel(i,j) == GRID_COLOR) &&
                 !(image.getPixel(i,j) == CIRCLE_COLOR))
            {
                biliniarInterpolation(i,j);
            }
        }
    }
}

void Drawarea::changeInterpolation( bool interpolate_ )
{
    drawFunction();
    if ( isolinesDrawn )
    {
        drawIsolines();
    }

    if ( interpolate_ )
    {
        interpolate();
        interpolated = true;
    }
    else
    {
        interpolated = false;
    }

    if ( gridMode )
    {
        drawGrid();
    }
    display->repaint();
    repaint();
}

void Drawarea::changeIsolines( bool drawIsolines_ )
{
    drawFunction();
    if ( drawIsolines_ )
    {
        drawIsolines();
        isolinesDrawn = true;
    }
    else
    {
        clearGrid();
        isolinesDrawn = false;
    }

    if ( interpolated )
    {
        interpolate();
    }

    if ( gridMode )
    {
        drawGrid();
    }
    display->repaint();
    repaint();
}

void Drawarea::changeGrid( bool drawGrid_ )
{
    drawFunction();
    if ( isolinesDrawn )
    {
        drawIsolines();
    }
    if ( interpolated )
    {
        interpolate();
    }

    if ( drawGrid_ )
    {
        drawGrid();
        gridMode = true;
    }
    else
    {
        gridMode = false;
    }
    display->repaint();
    repaint();
}

void Drawarea::changeParameters( int k, int m, float a, float b, float c, float d )
{
    clearGrid();
    setGridSize(k,m);
    function->setD(a,c,b,d);
    function->config();
    drawFunction();
    if ( isolinesDrawn )
    {
        drawIsolines();
    }

    if ( interpolated )
    {
        interpolate();
    }

    if ( gridMode )
    {
        drawGrid();
    }
    repaint();
}

void Drawarea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0,*image.getImage());
    painter.drawImage(0,0,*gridImage.getImage());
}
