#ifndef DOUBLEPICTURE_H
#define DOUBLEPICTURE_H

#include <QRgb>
#include "filter.h"

class DoublePicture: public Filter
{
    Q_OBJECT
public:
    DoublePicture(QObject *parent = nullptr);
    void apply(RawImage *inputImage_) override;

private:
    void countEmptyPixel(QPoint pixelCoord);
    bool checkPoint(QSize size, QPoint point);
    void processEmptyPoint(const QPoint &currentCoord );

    int red_av = 0;
    int green_av = 0;
    int blue_av = 0;
    int pixelsAmount = 0;
    RawImage *inputImage = nullptr;

};

#endif // DOUBLEPICTURE_H
