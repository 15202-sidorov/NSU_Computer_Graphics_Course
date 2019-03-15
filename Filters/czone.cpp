#include "czone.h"

CZone::CZone(QWidget *parent): Zone(parent)
{
    worker->start();
}

void CZone::setImage(QImage inputImage)
{
    if ( nullptr == currentFilter || isWorking )
    {
        return;
    }
    blockSignals(false);
    qimage = inputImage.scaled(ZONE_SIZE_WIDTH - 2, ZONE_SIZE_HEIGHT - 2);
    image->setImage(&qimage);
    emit doWork(image);
    isWorking = true;
}
