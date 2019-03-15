#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QSize>
#include <QImage>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QToolButton>
#include <QFileDialog>

#include "azone.h"
#include "bzone.h"
#include "czone.h"

#include "fsditherdialog.h"
#include "gammadialog.h"
#include "angledialog.h"
#include "aboutdialog.h"

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
    inline void setNewImage(QString filePath)
    {
        if ( nullptr != mainImage )
        {
            delete mainImage;
        }

        mainImage = new QImage(filePath);
        azone->setImage(*mainImage);
    }

    void handleBtoC();
    void handleCtoB();

private:

    Ui::MainWindow *ui;

    QImage *mainImage = nullptr;
    QScrollArea *scroll = new QScrollArea(this);
    QWidget *container = new QWidget(scroll);
    QHBoxLayout *mainLayout = new QHBoxLayout(container);
    QFileDialog *openFileDialog = new QFileDialog(0);
    QFileDialog *saveFileDialog = new QFileDialog(0);

    AZone *azone = new AZone(container);
    BZone *bzone = new BZone(container);
    CZone *czone = new CZone(container);
    FSDitherDialog *fsDitherDialog = new FSDitherDialog(0);
    AboutDialog *about = new AboutDialog(0);
    GammaDialog *gammaDialog = new GammaDialog(0);
    AngleDialog *angleDialog = new AngleDialog(0);

    void setActions();
    void configMenus();
    void configToolbar();
    void createMenus();
    void setConnections();

    QToolBar *toolbar;

    QMenu *fileMenu;
    QMenu *filtersMenu;
    QMenu *helpMenu;

    QAction *newFile;
    QAction *openFile;
    QAction *saveAs;
    QAction *select;
    QAction *copyBtoC;
    QAction *copyCtoB;
    QAction *blackToWhiteAction;
    QAction *negativeAction;
    QAction *floydDitherAction;
    QAction *robertsAction;
    QAction *orderedDitherAction;
    QAction *zoomAction;
    QAction *blurAction;
    QAction *sharpAction;
    QAction *embossAction;
    QAction *waterColorAction;
    QAction *gammaCorrectionAction;
    QAction *sobelAction;
    QAction *runAction;
    QAction *turnAction;
    QAction *aboutAction;

    static const int SPACE_BETWEEN_ZONES = 15;

};

#endif // MAINWINDOW_H
