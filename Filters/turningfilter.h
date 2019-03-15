#ifndef TURNINGFILTER_H
#define TURNINGFILTER_H

#include <QObject>
#include "filter.h"

# define M_PI           3.14159265358979323846

class TurningFilter : public Filter
{
    Q_OBJECT
public:
    explicit TurningFilter(QObject *parent = nullptr, int angle = 0);

    void apply(RawImage *inputImage) override;

private:
    int angle;

};

#endif // TURNINGFILTER_H
