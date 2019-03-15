#include "splineedit.h"

#include <QDebug>

SplineEdit::SplineEdit(QWidget *parent) : QWidget(parent)
{
    setFixedSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y);
    for (int i = 0; i < image.getImage()->width(); i++)
    {
        for (int j = 0; j < image.getImage()->height(); j++) {
            if ( i == width()/2 || j == height()/2 )
            {
                image.setPixel(i,j,LINE_DEFAULT_COLOR);
            }
            else {
                image.setPixel(i,j,FIELD_DEFAULT_COLOR);
            }

            pointsImage.setPixel(i,j,qRgba(0,0,0,0));
        }
    }
}

float SplineEdit::countSplineLength()
{
    float result = 0;
    float part_result = 0;
    float delta = 0.01f;
    float t = 0;
    float x = 0;
    float y = 0;
    float x_prev = 0;
    float y_prev = 0;
    QGenericMatrix<1, 4, float> Gx;
    QGenericMatrix<1, 4, float> Gy;
    QGenericMatrix<4, 1, float> T;
    splineLength.clear();
    for (int i = 1; i < basePoints.count() - 2; i++)
    {
        Gx(0,0) = basePoints[i-1].x();
        Gx(1,0) = basePoints[i].x();
        Gx(2,0) = basePoints[i+1].x();
        Gx(3,0) = basePoints[i+2].x();

        Gy(0,0) = basePoints[i-1].y();
        Gy(1,0) = basePoints[i].y();
        Gy(2,0) = basePoints[i+1].y();
        Gy(3,0) = basePoints[i+2].y();

        while (t <= 1)
        {
            T(0,0) = t * t * t;
            T(0,1) = t * t;
            T(0,2) = t;
            T(0,3) = 1;
            x = (T * (M_Matrix * Gx))(0, 0);
            y = (T * (M_Matrix * Gy))(0, 0);
            if ( t != 0 )
            {
                part_result += QLineF(QPointF(x,y),
                                      QPointF(x_prev, y_prev)).length();
            }
            x_prev = x;
            y_prev = y;
            t += delta;
        }

        splineLength.push_back(part_result);
        result += part_result;
        part_result = 0;
        t = 0;
    }

    return result;
}

QPointF SplineEdit::getSplineValue( float u )
{
    float l = length;
    float targetValue = u * l;
    float delta = 0.01f;
    float t = 0;
    float current_length = 0;
    float x = 0;
    float y = 0;
    float x_prev = 0;
    float y_prev = 0;
    QGenericMatrix<1, 4, float> Gx;
    QGenericMatrix<1, 4, float> Gy;
    QGenericMatrix<4, 1, float> T;

    for (int i = 1; i < splineLength.count() + 1; i++)
    {
        Gx(0,0) = basePoints[i-1].x();
        Gx(1,0) = basePoints[i].x();
        Gx(2,0) = basePoints[i+1].x();
        Gx(3,0) = basePoints[i+2].x();

        Gy(0,0) = basePoints[i-1].y();
        Gy(1,0) = basePoints[i].y();
        Gy(2,0) = basePoints[i+1].y();
        Gy(3,0) = basePoints[i+2].y();
        current_length += splineLength[i-1];
        if ( current_length >= targetValue ||
             fabs(current_length - targetValue) < EPS)
        {
            current_length -= splineLength[i-1];
            while( t <= 1 )
            {
                T(0,0) = t * t * t;
                T(0,1) = t * t;
                T(0,2) = t;
                T(0,3) = 1;
                x = (T * (M_Matrix * Gx))(0, 0);
                y = (T * (M_Matrix * Gy))(0, 0);

                if ( t != 0 )
                {
                    current_length += QLineF(QPointF(x,y),
                                             QPointF(x_prev, y_prev)).length();
                    if ( current_length >= targetValue ||
                         fabs(current_length - targetValue) < EPS )
                    {
                        return QPointF(x,y);
                    }
                }

                x_prev = x;
                y_prev = y;
                t += delta;
            }
            t = 0;
        }

    }

    return QPointF(-2 * WORLD_SIZE_X- 1,-2 * WORLD_SIZE_Y - 1);
}

void SplineEdit::mousePressEvent( QMouseEvent *event )
{
    for (int i = 0; i < basePoints.size(); i++)
    {
        if ( pointIsInCircle(event->pos(),
                             worldToPixel(basePoints[i]),
                             CIRCLE_RADIUS) )
        {
            if ( event->button() == Qt::LeftButton )
            {
                draggedPointIndex = i;
                return;
            }
            else
            {
                basePoints.remove(i);
                drawSpline();
                drawPoints();
                repaint();
                return;
            }
        }
    }

    basePoints.push_back(pixelToWorld(event->pos()));
    drawSpline();
    drawPoints();

    repaint();
    return;
}

void SplineEdit::mouseMoveEvent( QMouseEvent *event )
{
    if ( draggedPointIndex >= 0 )
    {
        basePoints[draggedPointIndex] = pixelToWorld(event->pos());
        drawPoints();
        drawSpline();
        repaint();
    }
}

void SplineEdit::mouseReleaseEvent( QMouseEvent *event )
{
    if ( draggedPointIndex >= 0 )
    {
        draggedPointIndex = -1;
    }
}

bool SplineEdit::pointIsInCircle( QPoint targetPoint, QPoint center, int radius )
{
    return QLineF(center,targetPoint).length() < (float)radius;
}

void SplineEdit::drawPoints()
{
    for (int j = 0; j < pointsImage.getImage()->height(); j++)
    {
        for (int i = 0; i < pointsImage.getImage()->width(); i++)
        {
            pointsImage.setPixel(i,j,qRgba(0,0,0,0));
        }

    }

    foreach(QPointF point, basePoints)
    {
        drawCircle(worldToPixel(point));
    }
}

void SplineEdit::drawCircle( QPoint center )
{
    int x0 = center.x();
    int y0 = center.y();
    int x = CIRCLE_RADIUS - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (CIRCLE_RADIUS << 1);
    while (x >= y)
    {
        pointsImage.setPixel(x0 + x, y0 + y,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 + y, y0 + x,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 - y, y0 + x,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 - x, y0 + y,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 - x, y0 - y,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 - y, y0 - x,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 + y, y0 - x,SIRCLES_DEFAULT_COLOR);
        pointsImage.setPixel(x0 + x, y0 - y,SIRCLES_DEFAULT_COLOR);

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
            err += dx - (CIRCLE_RADIUS << 1);
        }
    }
}

void SplineEdit::drawSpline()
{
    for (int j = 0; j < image.getImage()->height(); j++)
    {
        for (int i = 0; i < image.getImage()->width(); i++)
        {
            if ( i == width()/2 || j == height()/2 )
            {
                image.setPixel(i,j,LINE_DEFAULT_COLOR);
            }
            else {
                image.setPixel(i,j,FIELD_DEFAULT_COLOR);
            }
        }
    }

    for (int i = 1; i < basePoints.count() - 2; i++)
    {
        QGenericMatrix<1, 4, float> Gx;
        Gx(0,0) = basePoints[i-1].x();
        Gx(1,0) = basePoints[i].x();
        Gx(2,0) = basePoints[i+1].x();
        Gx(3,0) = basePoints[i+2].x();

        QGenericMatrix<1, 4, float> Gy;
        Gy(0,0) = basePoints[i-1].y();
        Gy(1,0) = basePoints[i].y();
        Gy(2,0) = basePoints[i+1].y();
        Gy(3,0) = basePoints[i+2].y();

        drawSplinePart(Gx,Gy);
    }

    length = countSplineLength();
}

void SplineEdit::drawSplinePart( QGenericMatrix<1,4, float> Gx,
                                 QGenericMatrix<1,4, float> Gy )
{
    QPoint knot0 = worldToPixel(QPointF(Gx(0,0), Gy(0,0)));
    QPoint knot1 = worldToPixel(QPointF(Gx(1,0), Gy(1,0)));
    QPoint knot2 = worldToPixel(QPointF(Gx(2,0), Gy(2,0)));
    QPoint knot3 = worldToPixel(QPointF(Gx(3,0), Gy(3,0)));
    if (    (knot0 - knot1).manhattanLength() +
            (knot1 - knot2).manhattanLength() +
            (knot2 - knot3).manhattanLength() <= 3)
    {
        if (image.getImage()->rect().contains(knot0, true))
        {
            image.setPixel(knot0.x(), knot0.y(), SPLINE_DEFAULT_COLOR);
        }
    }
    else
    {
        auto Gx_ = Split_Spline_Left_Matrix * Gx;
        auto Gy_ = Split_Spline_Left_Matrix * Gy;
        drawSplinePart(Gx_,Gy_);

        Gx_ = Split_Spline_Right_Matrix * Gx;
        Gy_ = Split_Spline_Right_Matrix * Gy;
        drawSplinePart(Gx_,Gy_);
    }

}

QPointF SplineEdit::pixelToWorld( QPoint point )
{
    QPointF newPoint;
    newPoint.setX((WORLD_SIZE_X * 2 * (point.x()-width()/2)  /width()));
    newPoint.setY((WORLD_SIZE_Y * 2 * (point.y()-height()/2) /height()));
    return newPoint;
}

QPoint SplineEdit::worldToPixel( QPointF point )
{
    QPoint newPoint;
    newPoint.setX((width() *  (point.rx()+WORLD_SIZE_X)) /(2 * WORLD_SIZE_X));
    newPoint.setY((height() * (point.ry()+WORLD_SIZE_Y)  /(2 * WORLD_SIZE_Y)));
    return newPoint;
}

void SplineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0,*image.getImage());
    painter.drawImage(0,0, *pointsImage.getImage());
}
