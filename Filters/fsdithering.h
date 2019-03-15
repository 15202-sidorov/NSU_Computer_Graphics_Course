#ifndef FSDITHERING_H
#define FSDITHERING_H

#include <QWidget>
#include <QColor>
#include <QVector>
#include "filter.h"

class FSDithering : public Filter
{
    Q_OBJECT
public:
    explicit FSDithering(QWidget *parent = nullptr);

    inline QColor getColors()
    {
        return qRgb(redN, greenN, blueN);
    }

    void apply(RawImage *inputImage) override;

public slots:
    inline void setColors(int inputRed,
                          int inputGreen,
                          int inputBlue)
    {
        redN = inputRed;
        greenN = inputGreen;
        blueN = inputBlue;
    }

private:
    int redN = 3;
    int greenN = 3;
    int blueN = 2;

    static constexpr float RIGHT_COEFFICIENT = 7.0f / 16.0f;
    static constexpr float BOTTOM_COEFFICIENT = 3.0f / 16.0f;
    static constexpr float BOTTOM_LEFT_COEFFICIENT = 5.0f / 16.0f;

};

#endif // FSDITHERING_H
