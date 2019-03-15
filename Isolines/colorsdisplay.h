#ifndef COLORSDISPLAY_H
#define COLORSDISPLAY_H

#include <QWidget>
#include <QPainter>
#include <QVector>

#include "rawimage.h"

class ColorsDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ColorsDisplay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void addColor(const QRgb &newColor);
    void paintNormal();
    void interpolate();

    inline QRgb getPixel(int x) { return image.getPixel(x,DEFAULT_SIZE_Y - 1); }
    inline int getColorsAmount() { return colorsAmount; }
    inline QRgb getColor(int i) { return colors[i]; }

signals:

public slots:

private:
    static const int DEFAULT_SIZE_X = 800;
    static const int DEFAULT_SIZE_Y = 100;

    void paintVertical(const QRgb &color, int x);
    int interpoateColor(int color1, int color2,
                        int color_index, int i,
                        int width);
    QVector<QRgb> colors;
    int colorsAmount = 0;
    QRgb DEFAULT_COLOR = qRgb(255,255,255);
    RawImage image = RawImage(new QImage(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, QImage::Format_ARGB32));
};

#endif // COLORSDISPLAY_H
