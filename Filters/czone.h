#ifndef CZONE_H
#define CZONE_H

#include "zone.h"
#include "filter.h"
#include "grayscalecolor.h"
#include "negativecolor.h"
#include "doublepicture.h"
#include "fsdithering.h"
#include "blurfilter.h"
#include "sobeloperator.h"
#include "ordereddither.h"
#include "aquerellfilter.h"
#include "sharpfilter.h"
#include "embosefilter.h"
#include "gammafilter.h"
#include "robertsfilter.h"
#include "turningfilter.h"

#include <QDebug>
#include <QThread>
#include <QFile>

class CZone: public Zone
{
    Q_OBJECT
public:
    explicit CZone(QWidget *parent = nullptr);
    void setImage(QImage inputImage);

    inline void setFilter(Filter *inputFilter)
    {
        currentFilter = inputFilter;
    }

    inline Filter *getFilter()
    {
        return currentFilter;
    }

    inline ~CZone()
    {
       checkFilter();
       worker->deleteLater();
       worker->exit();
    }

signals:
    void doWork(RawImage *inputImage);

public slots:
    inline void saveFile(QString filePath)
    {
        if ( QFile::exists(filePath) )
        {
            image->getImage()->save(filePath);
        }
        else
        {
            QFile newFile(filePath);
            newFile.open(QIODevice::ReadWrite);
            image->getImage()->save(filePath);
            newFile.close();
        }
    }

    inline void setGrayScaleColor()
    {
        checkFilter();
        currentFilter = new GrayScaleColor(0);
        connectNewFilter();
    }

    inline void setNoFilter()
    {
        checkFilter();
        currentFilter = nullptr;
    }

    inline void setNegativeColor()
    {
        checkFilter();
        currentFilter = new NegativeColor(0);
        connectNewFilter();
    }

    inline void setDoublePicture()
    {
        checkFilter();
        currentFilter = new DoublePicture(0);
        connectNewFilter();
    }

    inline void setFSDithering(int redN,
                               int greenN,
                               int blueN)
    {
        checkFilter();
        currentFilter = new FSDithering(0);
        connectNewFilter();
        FSDithering *fsPtr = (FSDithering *)currentFilter;
        fsPtr->setColors(redN, greenN, blueN);
    }

    inline void setBlurFilter()
    {
        checkFilter();
        currentFilter = new BlurFilter(0);
        connectNewFilter();
    }

    inline void setSobelOperator()
    {
        checkFilter();
        currentFilter = new SobelOperator(0);
        connectNewFilter();
    }

    inline void setOrderedDither()
    {
        checkFilter();
        currentFilter = new OrderedDither(0);
        connectNewFilter();
    }

    inline void setAquerellFilter()
    {
        checkFilter();
        currentFilter = new AquerellFilter(0);
        connectNewFilter();
    }

    inline void setSharpFilter()
    {
        checkFilter();
        currentFilter = new SharpFilter(0);
        connectNewFilter();
    }

    inline void setEmboseFilter()
    {
        checkFilter();
        currentFilter = new EmboseFilter(0);
        connectNewFilter();
    }

    inline void setGammaFilter(float gamma)
    {
        checkFilter();
        currentFilter = new GammaFilter(0,gamma);
        connectNewFilter();
    }

    inline void setRobertsOperator()
    {
        checkFilter();
        currentFilter = new RobertsFilter(0);
        connectNewFilter();
    }

    inline void setTurningFilter(int angle)
    {
        checkFilter();
        currentFilter = new TurningFilter(0,angle);
        connectNewFilter();
    }

    inline void refreshImage(const QImage &inputImage)
    {
        setImage(inputImage);
    }

    inline void repaintResult()
    {
        isWorking = false;
        repaint();
    }

private:

    inline void checkFilter()
    {
        if ( currentFilter != nullptr )
        {
            delete currentFilter;
        }
    }

    inline void connectNewFilter()
    {
        connect(this, SIGNAL(doWork(RawImage *)), currentFilter, SLOT(filterImage(RawImage*)));
        connect(currentFilter, SIGNAL(workDone()), this, SLOT(repaintResult()));
        currentFilter->moveToThread(worker);
    }

    Filter *currentFilter = nullptr;
    QThread *worker = new QThread(this);
    bool isWorking = false;

};

#endif // CZONE_H
