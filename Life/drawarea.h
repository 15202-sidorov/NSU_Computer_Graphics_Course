#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QImage>
#include <QRgb>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QStaticText>

#include <iomanip>
#include <sstream>

#include "fieldcontroller.h"
#include "rawimage.h"

#define M_PI (3.14159265358979323846)
#include <math.h>

class DrawArea : public QWidget
{
    Q_OBJECT
    /*
        setSize();
        uniquePtrs;
    */

public:
    typedef enum
    {
        NORMAL = 0,
        XOR = 1
    } Regime;

    explicit DrawArea     (QWidget *parent = 0, FieldController * fieldCtl = 0);

    void paintEvent       (QPaintEvent * event);
    void mouseMoveEvent   (QMouseEvent * event);
    void mousePressEvent  (QMouseEvent * event);

    inline QImage*          getImage         () { return image.getImage(); }
    inline FieldController* getField         () { return fieledCtl; }
    inline void             setPoligonSize   (int size) { POLIGON_SIZE = size; START_POINT = POLIGON_SIZE + PADDING; }
    inline int              getPoligonSize   () { return POLIGON_SIZE; }
    inline int              getTimerInterval () { return timerInterval; }
    inline int              getRegime        () { return currentRegime; }

    void refreshSize();

signals:

public slots:
    void invokeIteration  ();
    void newPoligonSize   (int size);
    void switchRun        (bool b);
    void startGame        ();
    void stopGame         ();
    void setTimerInterval (int interval);
    void setXOR           (bool b);
    void setReset         (bool b);
    void setImpactMode    (bool b);
    void clear            ();

private:
    typedef enum
    {
        /*
            Direction in which span is moving.
        */
        UPWARDS,
        DOWNWARDS
    } SpanDirection;

    void drawLine               (const QPoint &newPoint);
    void countNextCenter        (int i, int j);
    void drawPoligon            (int i, int j);
    void drawPoligons           ();
    void fillPoligonInDirection (QPoint mousePosition, const SpanDirection &direction, const QRgb &color);
    void fillPoligon            (QPoint mousePosition, const QRgb &color);
    void drawImpacts            (QPainter &painter);
    void fillPoligons           ();

    FieldController::OffsetCoordinate
    getPoligonCoordinateFromMousePoint (const QPoint &mouseLocation);

    QPoint
    getMouseLocationFromCoordinate (const FieldController::OffsetCoordinate &coordinate);

    QPoint &       getCenter     (int i, int j);
    QPoint &       getCenter     (const FieldController::OffsetCoordinate &coordinate);

    inline int     countDistance (const QPoint &p1, const QPoint &p2)
    {
        int dx = p1.x() - p2.x(); int dy = p1.y() - p2.y();
        return dx * dx + dy * dy;
    }

    int POLIGON_SIZE           = DEFAULT_POLIGON_SIZE;
    int START_POINT            = POLIGON_SIZE + PADDING;

    static const int PADDING                = 10;
    static const int ANGLE_COUNT            = 6;
    static const int DEFAULT_POLIGON_SIZE   = 35;
    static const int DEFAULT_TIMER_INTERVAL = 500;

    FieldController * fieledCtl;

    QRgb LINE_COLOR        = qRgb(0,0,0);
    QRgb ALIVE_CELL_COLOR  = qRgb(0,255,0);
    QRgb DEAD_CELL_COLOR   = qRgb(254,255,255);

    QPoint currentCenter = QPoint(START_POINT, START_POINT);
    QPoint currentPoint  = QPoint(currentCenter.x() + (int)(POLIGON_SIZE  * cos(M_PI/6)),
                                  currentCenter.y() - (int)(POLIGON_SIZE  * sin(M_PI/6)));
    std::vector<QPoint> centers;

    RawImage image =
            RawImage(new QImage(QSize( (int)(POLIGON_SIZE  * cos(M_PI/6)) * 2 * fieledCtl->getWidth() + 2 * POLIGON_SIZE,
                                       POLIGON_SIZE * 2 * fieledCtl->getHeight() + POLIGON_SIZE * 2),
                                QImage::Format_ARGB32));

    int timerInterval = DEFAULT_TIMER_INTERVAL;
    QTimer iterationTimer;
    Regime currentRegime = NORMAL;
    bool impactMode = false;
    FieldController::OffsetCoordinate prevCoordinate = FieldController::OffsetCoordinate(0,0);
};

#endif // DRAWAREA_H
