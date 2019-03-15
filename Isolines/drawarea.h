#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QVector>
#include <QMouseEvent>

#include "rawimage.h"
#include "colorsdisplay.h"
#include "function.h"

class Drawarea : public QWidget
{
    Q_OBJECT
public:
    explicit Drawarea(QWidget *parent = nullptr,
                      ColorsDisplay *inputDisplay = nullptr,
                      Function *inputFunction = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent (QMouseEvent * event);

signals:
    void refreshFunctionValues(float x, float y, float value);

public slots:
    void drawFunction();
    void drawIsolines();
    void changeInterpolation(bool interpolate_);
    void changeIsolines(bool drawIsonlines_);
    void changeGrid(bool drawGrid_);
    void changeParameters(int k, int m,
                          float a, float b,
                          float c, float d);
    void drawGridIsolines(float z);

private:
    static const int DEFAULT_SIZE_X = 1200;
    static const int DEFAULT_SIZE_Y = 800;
    static const int CIRCLE_SIZE = 10;

    QRgb CIRCLE_COLOR = qRgb(199,21,133);
    QRgb DEFAULT_COLOR = qRgb(255,255,255);
    QRgb ISOLINE_COLOR = qRgb(255,255,255);
    QRgb GRID_COLOR    = qRgb(0,0,0);

    ColorsDisplay *display;
    Function *function;
    RawImage image = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y,QImage::Format_ARGB32));
    RawImage gridImage = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, QImage::Format_ARGB32));

    int GRID_K = 10;
    int GRID_M = 10;

    void biliniarInterpolation(int i, int j);
    void drawGridVerictalLine(int j);
    void drawGridHorizontalLine(int i);
    void drawLine(QPoint currentPoint,
                  QPoint newPoint);
    void drawCircle(QPoint center);

    bool interpolated = false;
    void interpolate();
    inline void setGridSize(int k, int m)
    {
        GRID_K = k; GRID_M = m;
    }
    bool isolinesDrawn = true;
    bool gridMode = false;
    void drawGrid();
    void clearGrid();


    QRgb defineColor(int i, int j);
    float defineIsoline( float f1, float f2,
                          float z, float dx );

};

#endif // DRAWAREA_H
