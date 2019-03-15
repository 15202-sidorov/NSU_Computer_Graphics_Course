#ifndef FILTER_H
#define FILTER_H

#include <QImage>
#include <QDebug>
#include "rawimage.h"

class Filter: public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);

    virtual ~Filter() {}
    virtual void apply(RawImage *inputImage) = 0;

signals:
    void workDone();

public slots:
    void filterImage(RawImage *inputImage)
    {
        if ( !filterIsWorking )
        {
            filterIsWorking = true;
            apply(inputImage);
            filterIsWorking = false;
            emit workDone();
        }
    }

private:
    bool filterIsWorking = false;

};

#endif // FILTER_H
