#include "bzone.h"

#include <QDebug>

BZone::BZone(QWidget *parent) : Zone(parent)
{

}

void BZone::refreshImage( const QImage &inputImage )
{
    setImage( inputImage );
}


void BZone::setImage( QImage inputImage )
{
    blockSignals(false);
    qimage = inputImage.scaled(ZONE_SIZE_WIDTH - 2, ZONE_SIZE_HEIGHT - 2);
    image->setImage(&qimage);
    emit forwardImageToCZone(inputImage);
    repaint();
}
