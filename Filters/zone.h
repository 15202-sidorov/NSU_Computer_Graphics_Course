#ifndef ZONE_H
#define ZONE_H

#include <QWidget>
#include <QPainter>
#include <QRgb>
#include <QImage>
#include <QPainter>
#include "rawimage.h"

class Zone : public QWidget
{
    Q_OBJECT
public:
    explicit Zone(QWidget *parent = nullptr);
    explicit Zone(QWidget *parent, QImage inputImage);

    virtual ~Zone();

    virtual void setImage(QImage inputImage) = 0;

    void paintEvent(QPaintEvent *event);

    inline QImage getImage()
    {
        return qimage;
    }

signals:

public slots:
    inline void clearImage()
    {
        drawBorder(false);
        repaint();
        blockSignals(true);
    }

    void setImageOnly( QImage inputImage )
    {
        blockSignals(false);
        delete image;
        qimage = inputImage;
        image = new RawImage(&qimage);
        repaint();
    }

protected:
    static const int ZONE_SIZE_WIDTH  = 352;
    static const int ZONE_SIZE_HEIGHT = 352;

    QImage qimage;
    RawImage *image;

    void drawBorder(bool borderOnly);
    QRgb DEFAULT_ZONE_COLOR   = qRgb(255,255,255);
    QRgb DEFAULT_BORDER_COLOR = qRgb(0,0,0);

private:

    static const int BORDER_PADDING = 10;
};

#endif // ZONE_H
