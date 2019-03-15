#ifndef BLURFILTER_H
#define BLURFILTER_H

#include <QObject>
#include "filter.h"

class BlurFilter : public Filter
{
    Q_OBJECT
public:
    explicit BlurFilter(QObject *parent = nullptr);


    void apply( RawImage *inputImage ) override;

private:
    static constexpr float MATRIX_COEFFICIENT = 1/6.0f;

    static const int KERNEL_SIZE_X = 3;
    static const int KERNEL_SIZE_Y = 3;
    static
    const int kernel[KERNEL_SIZE_X][KERNEL_SIZE_Y];
    void checkColor( int *color_ptr );

};

#endif // BLURFILTER_H
