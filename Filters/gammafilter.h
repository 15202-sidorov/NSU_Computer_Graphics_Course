#ifndef GAMMAFILTER_H
#define GAMMAFILTER_H

#include <cmath>
#include <QObject>

#include "filter.h"

class GammaFilter : public Filter
{
    Q_OBJECT
public:
    explicit GammaFilter(QObject *parent = nullptr, float gamma = 1.0);

    void apply(RawImage *inputImage) override;

private:
    float gamma;
};

#endif // GAMMAFILTER_H
