#ifndef SPLINEEDIT_H
#define SPLINEEDIT_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QLineF>
#include <math.h>

#include "rawimage.h"

class SplineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit SplineEdit(QWidget *parent = nullptr);

    inline bool isEmpty()
    {
        return !basePoints.size();
    }

    inline void clearBasePoints()
    {
        basePoints.clear();
    }

    void    drawSpline();
    void    drawPoints();

    void paintEvent(QPaintEvent *event);

signals:

public slots:
    QPointF getSplineValue(float u);

private:
    const float Ms[16] =
    {
            -1,  3, -3,  1,
             3, -6,  3,  0,
            -3,  0,  3,  0,
             1,  4,  1,  0
    };

    const float Sl[16] =
    {
            4, 4, 0, 0,
            1, 6, 1, 0,
            0, 4, 4, 0,
            0, 1, 6, 1
    };

    const float Sr[16] =
    {
            1, 6, 1, 0,
            0, 4, 4, 0,
            0, 1, 6, 1,
            0, 0, 4, 4
    };

    static const int DEFAULT_SIZE_X = 1200;
    static const int DEFAULT_SIZE_Y = 800;
    static const int CIRCLE_RADIUS = 8;

    QVector<QPointF> basePoints;
    QVector<float>   splineLength;

    RawImage image = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y,QImage::Format_ARGB32));
    RawImage pointsImage = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, QImage::Format_ARGB32));

    QRgb FIELD_DEFAULT_COLOR   = qRgb(0,0,0);
    QRgb SPLINE_DEFAULT_COLOR  = qRgb(255,255,255);
    QRgb SIRCLES_DEFAULT_COLOR = qRgb(244, 66, 149);
    QRgb LINE_DEFAULT_COLOR    = qRgb(0,204,0);

    QGenericMatrix<4,4,float> M_Matrix =
            QGenericMatrix<4,4,float>(Ms) / 6.0f;
    QGenericMatrix<4,4,float> Split_Spline_Right_Matrix =
            QGenericMatrix<4,4,float>(Sr) / 8.0f;
    QGenericMatrix<4,4,float> Split_Spline_Left_Matrix =
            QGenericMatrix<4,4,float>(Sl) / 8.0f;

    float countSplineLength();

    void mousePressEvent   (QMouseEvent *event);
    void mouseMoveEvent    (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    int draggedPointIndex = -1;

    float length = 0;

    QPointF pixelToWorld(QPoint  point);
    QPoint  worldToPixel(QPointF point);

    void    drawCircle(QPoint center);
    void    drawSplinePart(QGenericMatrix<1,4,float> Gx, QGenericMatrix<1,4,float> Gy);

    bool    pointIsInCircle(QPoint targetPoint,
                            QPoint center,
                            int radius);

    static constexpr float WORLD_SIZE_X = 1;
    static constexpr float WORLD_SIZE_Y = 1;
    static constexpr float EPS = 0.000001f;
};

#endif // SPLINEEDIT_H
