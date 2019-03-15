#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H

#include <QObject>
#include "filter.h"
#include "grayscalecolor.h"

class SobelOperator : public Filter
{
    Q_OBJECT
public:
    explicit SobelOperator(QObject *parent = nullptr);
    void apply(RawImage *inputImage);

private:
    static const int KERNEL_SIZE_X = 3;
    static const int KERNEL_SIZE_Y = 3;

    static const int kernel_x[KERNEL_SIZE_X][KERNEL_SIZE_Y];

    static const int kernel_y[KERNEL_SIZE_X][KERNEL_SIZE_Y];

    void checkColor(float *color_ptr);

};

#endif // SOBELOPERATOR_H
