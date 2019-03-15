#ifndef SHARPFILTER_H
#define SHARPFILTER_H

#include <QObject>
#include <QVector>

#include "filter.h"

class SharpFilter : public Filter
{
    Q_OBJECT
public:
    explicit SharpFilter(QObject *parent = nullptr);


    void apply(RawImage *inputImage);

private:
    static const int KERNEL_SIZE_X = 3;
    static const int KERNEL_SIZE_Y = 3;
    static const int kernel[KERNEL_SIZE_X][KERNEL_SIZE_Y];

    void checkColor( float &color );
};

#endif // SHARPFILTER_H
