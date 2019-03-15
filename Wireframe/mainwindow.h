#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

#include "splineedit.h"
#include "figure3ddisplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setNextFigure();
    void setFigureRotateMode(bool isOn);
    void createFigure();
    void deleteCurrentFigure();
    void applyChanges();
    void setZn(float zn, float zf);

private:
    Ui::MainWindow *ui;

    void setEdits();

    Figure3DDisplay *figure     = new Figure3DDisplay();
    QScrollArea     *scroll     = new QScrollArea(this);
    QWidget         *container  = new QWidget(scroll);
    QVBoxLayout     *mainLayout = new QVBoxLayout(scroll);

    QLabel *figureLabel = new QLabel("Figure 0");
    QLabel *kLabel = new QLabel("k: ");
    QLabel *nLabel = new QLabel("n: ");
    QLabel *mLabel = new QLabel("m: ");

    QLineEdit *kEdit = new QLineEdit;
    QLineEdit *nEdit = new QLineEdit;
    QLineEdit *mEdit = new QLineEdit;

    QLabel *aLabel = new QLabel("a: ");
    QLabel *bLabel = new QLabel("b: ");
    QLabel *cLabel = new QLabel("c: ");
    QLabel *dLabel = new QLabel("d: ");

    QLineEdit *aEdit = new QLineEdit;
    QLineEdit *bEdit = new QLineEdit;
    QLineEdit *cEdit = new QLineEdit;
    QLineEdit *dEdit = new QLineEdit;

    QLabel *rLabel = new QLabel("R: ");
    QLabel *gLabel = new QLabel("G: ");
    QLabel *blLabel = new QLabel("B: ");
    QLineEdit *rEdit = new QLineEdit;
    QLineEdit *gEdit = new QLineEdit;
    QLineEdit *blEdit = new QLineEdit;

    QLabel *swLabel = new QLabel("sw: ");
    QLabel *shLabel = new QLabel("sh: ");
    QLabel *znLabel = new QLabel("zn: ");
    QLabel *zfLabel = new QLabel("zf: ");
    QLineEdit *swEdit = new QLineEdit;
    QLineEdit *shEdit = new QLineEdit;
    QLineEdit *znEdit = new QLineEdit;
    QLineEdit *zfEdit = new QLineEdit;

    QPushButton *nextFigureButton = new QPushButton("Next");
    QPushButton *rotateFigureButton = new QPushButton("Rotate figure");
    QPushButton *newFigureButton = new QPushButton("New");
    QPushButton *deleteFigureButton = new QPushButton("Delete");
    QPushButton *applyButton = new QPushButton("Apply");

    QGridLayout *optionsLayout = new QGridLayout();
    QVBoxLayout *splinesLayout = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    static const int TEXTEDIT_SIZE_X = 60;
    static const int TEXTEDIT_SIZE_Y = 40;

    Figure3D *currentFigure = nullptr;
    int currentFigureIndex = 0;

    QVector<Figure3D> figures;

};

#endif // MAINWINDOW_H
