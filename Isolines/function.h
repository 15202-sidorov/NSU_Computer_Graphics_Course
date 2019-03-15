#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QDebug>

class Function : public QObject
{
    Q_OBJECT
public:
    explicit Function(QObject *parent = nullptr);
    virtual float calculate(float x, float y) = 0;
    virtual void config() = 0;

    void setD(float mx, float my, float x, float y)
    {
        minX = mx;
        minY = my;
        maxX = x;
        maxY = y;
    }

    inline float getMinX() { return minX; }
    inline float getMinY() { return minY; }
    inline float getMaxX() { return maxX; }
    inline float getMaxY() { return maxY; }
    inline float getFunctionMin() { return functionMin; }
    inline float getFunctionMax() { return functionMax; }

signals:

public slots:

protected:
    float minX = 0;
    float minY = 0;
    float maxX = 0;
    float maxY = 0;
    float functionMin = 0;
    float functionMax = 0;

    float dx = 0.1;
    float dy = 0.1;
};

#endif // FUNCTION_H
