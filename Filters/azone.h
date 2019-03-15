#ifndef AZONE_H
#define AZONE_H

#include "zone.h"
#include <QRect>
#include <QMouseEvent>

class AZone : public Zone
{
    Q_OBJECT
public:
    explicit AZone (QWidget *parent = nullptr);

    void setImage (QImage inputImage) override;

    void mousePressEvent       (QMouseEvent * mouseEvent);
    void mouseReleaseEvent     (QMouseEvent * mouseEvent);
    void mouseMoveEvent        (QMouseEvent * mouseEvent);

signals:
    void newImage( QImage image );

public slots:
    inline void emitNewImage()
    {
        emit newImage(originalImage.copy(windowRect)) ;
    }


private:
    void drawWindow      (QPoint center);
    void countWindowSize ();
    void checkBorders    (QPoint &start, QPoint &end);

    QRect windowRect;

    QSize originalSize;
    QSize resultSize;
    QSize windowSize;

    QImage originalImage;

    static const int WINDOW_WIDTH  = 350;
    static const int WINDOW_HEIGHT = 350;
    static const int DASH_AMOUNT = 50;

    static const int WINDOW_BORDER_PADDING = 4;
    QRgb DEFAULT_WINDOW_BORDER_COLOR = qRgb(255,255,255);

};

#endif // AZONE_H
