#ifndef TARGETFUNCTION_H
#define TARGETFUNCTION_H

#include <QObject>

#include "function.h"

class TargetFunction : public Function
{
    Q_OBJECT
public:
    explicit TargetFunction(QObject *parent = nullptr);

    float calculate(float x, float y) override;
    void config() override;

signals:

public slots:
};

#endif // TARGETFUNCTION_H
