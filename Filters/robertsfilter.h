#ifndef ROBERTSFILTER_H
#define ROBERTSFILTER_H

#include <QObject>

#include "filter.h"
#include "grayscalecolor.h"

class RobertsFilter : public Filter
{
    Q_OBJECT
public:
    explicit RobertsFilter(QObject *parent = nullptr);

    void apply(RawImage *inputImage) override;

signals:

public slots:

private:
    void checkColor(int &color);

};

#endif // ROBERTSFILTER_H
