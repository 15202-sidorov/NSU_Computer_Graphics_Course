#ifndef BZONE_H
#define BZONE_H

#include "zone.h"

class BZone : public Zone
{
    Q_OBJECT
public:
    explicit BZone(QWidget *parent = nullptr);

    void setImage(QImage inputImage);


signals:
    void forwardImageToCZone(const QImage &forwardImage);

public slots:
    void refreshImage(const QImage &inputImage);

private:

};

#endif // BZONE_H
