#ifndef NEGATIVECOLOR_H
#define NEGATIVECOLOR_H

#include "filter.h"

class NegativeColor: public Filter
{
    Q_OBJECT
public:
    NegativeColor(QObject *parent = nullptr);

    void apply(RawImage *inputImage) override;
};

#endif // NEGATIVECOLOR_H
