#include "targetfunction.h"

#include <QDebug>

TargetFunction::TargetFunction(QObject *parent) : Function(parent)
{

}

void TargetFunction::config()
{
    float currentX = minX;
    float currentY = minY;
    functionMax = calculate(currentX, currentY);
    functionMin = calculate(currentX, currentY);
    float value = 0;

    while ( currentY < maxY )
    {
        while ( currentX < maxX )
        {
            value = calculate(currentX, currentY);
            if ( value > functionMax )
            {
                functionMax = value;
            }

            if ( value < functionMin )
            {
                functionMin = value;
            }

            currentX += dx;
        }

        currentX = minX;
        currentY += dy;
    }
}

float TargetFunction::calculate( float x, float y )
{
    return cos(x) * y * y + cos(y) * x * x;
}
