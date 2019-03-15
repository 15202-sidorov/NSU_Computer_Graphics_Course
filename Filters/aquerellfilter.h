#ifndef AQUERELLFILTER_H
#define AQUERELLFILTER_H

#include <QObject>
#include <vector>

#include "filter.h"

class AquerellFilter : public Filter
{
    Q_OBJECT
public:
    explicit AquerellFilter(QObject *parent = nullptr);

    void apply(RawImage *inputImage) override;

private:
    void calculateColor(RawImage *inputImage,
                        RawImage *median,
                        int x, int y);

    void calculateContur(RawImage *inputImage,
                         RawImage *median,
                         int x, int y);

    void checkColor(int &color);

    static const int KERNEL_WIDTH = 3;
    static const int KERNEL_HEIGHT = 3;

    static const float kernel[KERNEL_WIDTH][KERNEL_HEIGHT];

};

#endif // AQUERELLFILTER_H
