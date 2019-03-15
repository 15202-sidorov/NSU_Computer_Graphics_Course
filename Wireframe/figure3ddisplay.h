#ifndef FIGURE3DDISPLAY_H
#define FIGURE3DDISPLAY_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QRgb>

#include "rawimage.h"
#include "splineedit.h"
#include "figure3d.h"
#include "camera.h"
#include "cube.h"

# define M_PI 3.14159265358979323846

class Figure3DDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit Figure3DDisplay(QWidget *parent = nullptr);
    ~Figure3DDisplay();

    inline void addFigure(Figure3D *newFigure)
    {
        figures.push_back(newFigure);
    }

    void drawProjection();

    void deleteFigure(int i);

    inline Figure3D *getFigure(int i)
    {
        return figures[i];
    }

    inline void displayOneOnly(int i)
    {
        currentFigureIndex = i;
    }

    inline void displayAll()
    {
        currentFigureIndex = -1;
    }

    inline int figuresCount()
    {
        return figures.size();
    }

    inline Camera *getCamera() { return camera; }

    void mouseMoveEvent        (QMouseEvent  *event);
    void mousePressEvent       (QMouseEvent  *event);
    void wheelEvent            (QWheelEvent  *event);
    void paintEvent            (QPaintEvent  *event);

signals:

public slots:

private:
     void drawProjection(Figure3D *figure);
     void drawCube();

     void drawLine(QPoint currentPoint, QPoint newPoint, QRgb color);

     static const int DEFAULT_SIZE_X = 1200;
     static const int DEFAULT_SIZE_Y = 800;

     RawImage image = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y,QImage::Format_ARGB32));

     QVector<Figure3D *> figures;
     int currentFigureIndex = -1;

     Cube   *cube =     new Cube();
     Camera *camera =   new Camera();

     QRgb FIELD_DEFAULT_COLOR   = qRgb(0,0,0);
     QRgb CUBE_DEFAULT_COLOR    = qRgb(0,204,0);

     float deltaPhi = 2 * M_PI / 500;
     QPoint mousePos = QPoint(0,0);

     QPoint worldToPixel(QPointF point);

};

#endif // FIGURE3DDISPLAY_H
