#include "figure3ddisplay.h"

#include <QDebug>

Figure3DDisplay::Figure3DDisplay(QWidget *parent) :
                                 QWidget(parent)
{
    setFixedSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y);

    for (int j = 0; j < height(); j++)
    {
        for (int i = 0; i < width(); i++)
        {
            image.setPixel(i,j,FIELD_DEFAULT_COLOR);
        }
    }
}


Figure3DDisplay::~Figure3DDisplay()
{
    for (int i = 0; i < figures.size(); i++)
    {
        delete figures[i];
    }
}

void Figure3DDisplay::deleteFigure(int i)
{
    if ( figures.size() == 1 )
    {
        figures[0]->getSpline()->clearBasePoints();
        figures[0]->getSpline()->drawSpline();
        figures[0]->getSpline()->drawPoints();
        figures[0]->getSpline()->repaint();
        figures[0]->buildFigure();
        drawProjection();
        return;
    }
    delete figures[i];
    figures.remove(i);
}

void Figure3DDisplay::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
    {
        camera->incZn();
    }
    else if (event->delta() < 0 )
    {
        camera->decZn();
    }

    drawProjection();
    repaint();
}

void Figure3DDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if ( figures.size() <= 0 )
    {
        return;
    }

    QPoint diff = event->pos() - mousePos;
    bool rotated = false;
    if ( diff.x() != 0 )
    {
        if ( currentFigureIndex == -1 )
        {
            camera->rotateWorldAroundX(deltaPhi * diff.x());
        }
        else
        {
            figures[currentFigureIndex]->rotateAroundY(deltaPhi * diff.x());
        }
        rotated = true;
    }

    if ( diff.y() != 0 )
    {
        if ( currentFigureIndex == -1 )
        {
            camera->rotateWorldAroundZ(deltaPhi * diff.y());
        }
        else
        {
            figures[currentFigureIndex]->rotateAroundX(deltaPhi * diff.y());
        }
        rotated = true;
    }

    if ( rotated )
    {
        mousePos = event->pos();
        drawProjection();
        repaint();
    }
}

void Figure3DDisplay::mousePressEvent( QMouseEvent *event   )
{
    if ( currentFigureIndex == -1 )
    {
        for (int i = 0; i < figures.size(); i++)
        {
             figures[i]->buildFigure();
        }
    }
    else
    {
        figures[currentFigureIndex]->buildFigure();
    }
    drawProjection();
    repaint();
}

void Figure3DDisplay::drawLine( QPoint currentPoint,
                                QPoint newPoint,
                                QRgb color)
{
    QPoint prevPoint = currentPoint;
    currentPoint = newPoint;

    const int deltaX = abs(currentPoint.x() - prevPoint.x());
    const int deltaY = abs(currentPoint.y() - prevPoint.y());

    const int signX  = prevPoint.x() < currentPoint.x() ? 1 : -1;
    const int signY  = prevPoint.y() < currentPoint.y() ? 1 : -1;

    int error = deltaX - deltaY;
    image.setPixel(prevPoint.x(), prevPoint.y(), color);
    while ( currentPoint.x() != prevPoint.x() || currentPoint.y() != prevPoint.y() )
    {
        image.setPixel(prevPoint.x(), prevPoint.y() , color);

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


void Figure3DDisplay::drawProjection()
{
    for (int j = 0; j < height(); j++)
    {
        for (int i = 0; i < width(); i++)
        {
            image.setPixel(i,j,FIELD_DEFAULT_COLOR);
        }
    }

    if ( currentFigureIndex == -1 )
    {
        for (int i = 0; i < figures.size(); i++)
        {
            drawProjection(figures[i]);
        }
    }
    else
    {
        drawProjection(figures[currentFigureIndex]);
    }

    drawCube();
}

void Figure3DDisplay::drawProjection(Figure3D *figure)
{
    if ( figure->getSpline()->isEmpty() )
    {
        return;
    }

    QPoint currentPoint;
    QPoint prevPoint;

    QPointF proj1;
    QPointF proj2;

    float n = figure->getN();
    float m = figure->getM();
    float k = figure->getK();

    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < m; j++)
        {
            auto vec2 = figure->getBaseKnot(i*(m+1) + j+1);
            auto vec1 = figure->getClass1Knot(i*m + j);
            proj1 = camera->getProjection(vec1(0,0), vec1(1,0), vec1(2,0));
            for (int t = 0; t < k-1; t++)
            {
                vec2 = figure->getClass1kKnot((i*m + j)*(k-1) + t);
                proj2 = camera->getProjection(vec2(0,0), vec2(1,0), vec2(2,0));
                currentPoint = worldToPixel(proj1);
                prevPoint = worldToPixel(proj2);
                drawLine(prevPoint, currentPoint, figure->getColor());
                proj1 = proj2;
            }
            vec2 =  figure->getBaseKnot(i*(m+1) + j+1);
            proj2 = camera->getProjection(vec2(0,0), vec2(1,0), vec2(2,0));

            drawLine(worldToPixel(proj1), worldToPixel(proj2), figure->getColor());
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m+1; j++)
        {
            auto vec2 = figure->getBaseKnot((i+1)*(m+1) + j);
            auto vec1 = figure->getClass2Knot(i*(m+1) + j);
            proj1 = camera->getProjection(vec1(0,0), vec1(1,0), vec1(2,0));
            for (int t = 0; t < k-1; t++)
            {
                vec2 = figure->getClass2kKnot((i*(m+1) + j)*(k-1) + t);
                proj2 = camera->getProjection(vec2(0,0), vec2(1,0), vec2(2,0));
                currentPoint = worldToPixel(proj1);
                prevPoint = worldToPixel(proj2);
                drawLine(prevPoint, currentPoint, figure->getColor());
                proj1 = proj2;
            }
            vec2 =  figure->getBaseKnot((i+1)*(m+1) + j);
            proj2 = camera->getProjection(vec2(0,0), vec2(1,0), vec2(2,0));

            drawLine(worldToPixel(proj1), worldToPixel(proj2), figure->getColor());
        }
    }
}

void Figure3DDisplay::drawCube()
{
    QPointF proj1;
    QPointF proj2;
    QGenericMatrix<1,3,float> currentEdge1;
    QGenericMatrix<1,3,float> currentEdge2;

    for (int i = 0; i < cube->edges.size(); i++)
    {
        currentEdge1 = cube->edges[i][0];
        currentEdge2 = cube->edges[i][1];
        proj1 = camera->getProjection(currentEdge1(0,0), currentEdge1(1,0), currentEdge1(2,0));
        proj2 = camera->getProjection(currentEdge2(0,0), currentEdge2(1,0), currentEdge2(2,0));
        drawLine(worldToPixel(proj1), worldToPixel(proj2), CUBE_DEFAULT_COLOR);
    }
}

QPoint Figure3DDisplay::worldToPixel(QPointF point)
{
    QPoint newPoint;
    newPoint.setX((width() *  (point.rx()+camera->getWidth()))  /(2 * camera->getWidth()));
    newPoint.setY((height() * (point.ry()+camera->getHeight())  /(2 * camera->getHeight())));
    return newPoint;
}

void Figure3DDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image.getImage());
}
