#include "mainwindow.h"
#include <QApplication>

#include "fieldgetter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FieldController *field = new FieldController();
    MainWindow w(0, field);
    w.setBaseSize(800, 500);
    w.show();

    return a.exec();


}
