#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include "blurfilter.h"
#include "filter.h"
#include "sharpfilter.h"
#include "embosefilter.h"
#include "grayscalecolor.h"
#include "rawimage.h"
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainWindow w;
     w.show();

    Filter *myfilter = new BlurFilter(0);
//    QImage original = QImage(QString::fromStdString("D:\\g15202_Sidorov\\Filters\\FIT_Sidorov_Ilia_Filters_Data\\Lena"));
//    for (int i = 0; i < 100; i++)
//    {
//        QFile newFile(QString::fromStdString("D:\\g15202_Sidorov\\Filters\\test\\" + std::to_string(i) + ".bmp"));
//        newFile.open(QIODevice::ReadWrite);
//        original.save(QString::fromStdString("D:\\g15202_Sidorov\\Filters\\test\\" + std::to_string(i)+ ".bmp"));
//        newFile.close();
//    }

//    QVector<RawImage> raws;

//    for (int i = 0; i < 100; i++)
//    {
//        QImage *array = new QImage(QString::fromStdString("D:\\g15202_Sidorov\\Filters\\test\\" + std::to_string(i) + ".bmp"));
//        raws.append(RawImage(array));
//    }


//    QElapsedTimer timer;
//    qDebug() << "Timer started";
//    timer.start();
//    for (int i = 0; i < 100; i++)
//    {
//        myfilter->apply(&raws[i]);
//    }

//    qDebug() << timer.elapsed() << '\n';


    return a.exec();
}
