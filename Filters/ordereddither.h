#ifndef ORDEREDDITHER_H
#define ORDEREDDITHER_H

#include <QObject>
#include "filter.h"

class OrderedDither : public Filter
{
    Q_OBJECT
public:
    explicit OrderedDither(QObject *parent = nullptr);

    void apply(RawImage *inputImage) override;

private:
    static const int BATER[8][8];

    int BAYER[16][16];

};

#endif // ORDEREDDITHER_H
