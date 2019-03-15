#ifndef GRAYSCALECOLOR_H
#define GRAYSCALECOLOR_H

#include "filter.h"

class GrayScaleColor: public Filter
{
    Q_OBJECT
public:
    GrayScaleColor(QObject *parent = nullptr);

    void apply(RawImage *inputImage) override;

private:
    void checkColor( float *color );

};

#endif // GRAYSCALECOLOR_H
