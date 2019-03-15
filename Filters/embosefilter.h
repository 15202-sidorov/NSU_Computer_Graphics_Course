#ifndef EMBOSEFILTER_H
#define EMBOSEFILTER_H

#include <QObject>

#include "filter.h"

class EmboseFilter : public Filter
{
    Q_OBJECT
public:
    explicit EmboseFilter(QObject *parent = nullptr);
    void apply(RawImage *inputImage) override;

private:
    static const int KERNEL_SIZE_X = 3;
    static const int KERNEL_SIZE_Y = 3;

    static const int kernel[KERNEL_SIZE_X][KERNEL_SIZE_Y];

    void checkColor( float &color );
};

#endif // EMBOSEFILTER_H
