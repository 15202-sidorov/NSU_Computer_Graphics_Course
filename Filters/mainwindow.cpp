#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toolbar = addToolBar("MainToolBar");

    createMenus();
    configToolbar();
    configMenus();
    setActions();

    mainLayout->setSpacing(SPACE_BETWEEN_ZONES);

    mainLayout->addWidget(azone);
    mainLayout->addWidget(bzone);
    mainLayout->addWidget(czone);

    setConnections();

    container->setLayout(mainLayout);

    scroll->setWidget(container);

    setCentralWidget(scroll);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    filtersMenu = menuBar()->addMenu(tr("&Filters"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    newFile = new QAction(style()->standardIcon(QStyle::SP_FileIcon),tr("&New File"), this);
    openFile = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton),tr("&Open File"), this);
    saveAs = new QAction(style()->standardIcon(QStyle::SP_FileDialogNewFolder), tr("&Save As"), this);
    select = new QAction(style()->standardIcon(QStyle::SP_FileDialogContentsView),tr("&Select"),this);
    copyBtoC = new QAction(tr("&BtoC"),this);
    copyCtoB = new QAction("CtoB",this);
    blackToWhiteAction = new QAction("B&W",this);
    negativeAction = new QAction("Negative",this);
    floydDitherAction = new QAction("FSDither",this);
    orderedDitherAction = new QAction("OrdDither",this);
    zoomAction = new QAction("x2",this);
    blurAction = new QAction("Blur",this);
    sharpAction = new QAction("Sharp",this);
    embossAction = new QAction("Embass",this);
    waterColorAction = new QAction("Water Color",this);
    gammaCorrectionAction = new QAction("Gamma Correction",this);
    sobelAction = new QAction("Sobel",this);
    robertsAction = new QAction("Roberts",this);
    turnAction = new QAction("Turn",this);
    runAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay),tr("&Run"),this);
    aboutAction = new QAction(style()->standardIcon(QStyle::SP_TitleBarContextHelpButton),tr("&About"),this);
}

void MainWindow::configToolbar()
{
    toolbar->addAction(newFile);
    toolbar->addAction(openFile);
    toolbar->addAction(saveAs);
    toolbar->addSeparator();
    toolbar->addAction(copyBtoC);
    toolbar->addAction(copyCtoB);
    toolbar->addAction(select);
    toolbar->addSeparator();
    toolbar->addAction(blackToWhiteAction);
    toolbar->addAction(negativeAction);
    toolbar->addAction(floydDitherAction);
    toolbar->addAction(orderedDitherAction);
    toolbar->addAction(zoomAction);
    toolbar->addAction(blurAction);
    toolbar->addAction(sharpAction);
    toolbar->addAction(embossAction);
    toolbar->addAction(waterColorAction);
    toolbar->addAction(gammaCorrectionAction);
    toolbar->addAction(sobelAction);
    toolbar->addAction(robertsAction);
    toolbar->addAction(turnAction);
    toolbar->addAction(runAction);
    toolbar->addAction(aboutAction);
}

void MainWindow::setActions()
{

}

void MainWindow::setConnections()
{
    connect(copyBtoC, SIGNAL(triggered()),
            this, SLOT(handleBtoC()));
    connect(copyCtoB, SIGNAL(triggered()),
            this, SLOT(handleCtoB()));

    connect(newFile, SIGNAL(triggered()),
            azone, SLOT(clearImage()));

    connect(runAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(newFile, SIGNAL(triggered()),
            bzone, SLOT(clearImage()));
    connect(newFile, SIGNAL(triggered()),
            czone, SLOT(clearImage()));

    connect(openFile, SIGNAL(triggered()),
            openFileDialog, SLOT(show()));
    connect(openFileDialog, SIGNAL(fileSelected(QString)),
            this, SLOT(setNewImage(QString)));

    connect(saveAs, SIGNAL(triggered()),
            saveFileDialog, SLOT(show()));
    connect(saveFileDialog, SIGNAL(fileSelected(QString)),
            czone, SLOT(saveFile(QString)));

    connect(azone, SIGNAL(newImage(const QImage &)),
            bzone, SLOT(refreshImage(const QImage &)));
    connect(bzone, SIGNAL(forwardImageToCZone(QImage)),
            czone, SLOT(refreshImage(QImage)));

    connect(blackToWhiteAction, SIGNAL(triggered()),
            czone, SLOT(setGrayScaleColor()));
    connect(blackToWhiteAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(negativeAction, SIGNAL(triggered()),
            czone, SLOT(setNegativeColor()));
    connect(negativeAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(floydDitherAction, SIGNAL(triggered()),
            fsDitherDialog, SLOT(show()));
    connect(fsDitherDialog, SIGNAL(valuesUpdated(int,int,int)),
            czone, SLOT(setFSDithering(int, int, int)));
    connect(fsDitherDialog, SIGNAL(valuesUpdated(int,int,int)),
            azone, SLOT(emitNewImage()));

    connect(orderedDitherAction, SIGNAL(triggered()),
            czone, SLOT(setOrderedDither()));
    connect(orderedDitherAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(zoomAction, SIGNAL(triggered()),
            czone, SLOT(setDoublePicture()));
    connect(zoomAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(blurAction, SIGNAL(triggered()),
            czone, SLOT(setBlurFilter()));
    connect(blurAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(sharpAction, SIGNAL(triggered()),
            czone, SLOT(setSharpFilter()));
    connect(sharpAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(embossAction, SIGNAL(triggered()),
            czone, SLOT(setEmboseFilter()));
    connect(embossAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(waterColorAction, SIGNAL(triggered()),
            czone, SLOT(setAquerellFilter()));
    connect(waterColorAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(gammaCorrectionAction, SIGNAL(triggered()),
            gammaDialog, SLOT(show()));
    connect(gammaDialog, SIGNAL(gammaValueChanged(float)),
            czone, SLOT(setGammaFilter(float)));
    connect(gammaDialog, SIGNAL(gammaValueChanged(float)),
            azone, SLOT(emitNewImage()));

    connect(turnAction, SIGNAL(triggered()),
            angleDialog, SLOT(show()));
    connect(angleDialog, SIGNAL(angleValueChanged(int)),
            czone, SLOT(setTurningFilter(int)));
    connect(angleDialog, SIGNAL(angleValueChanged(int)),
            azone, SLOT(emitNewImage()));

    connect(sobelAction, SIGNAL(triggered()),
            czone, SLOT(setSobelOperator()));
    connect(sobelAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(robertsAction, SIGNAL(triggered()),
            czone, SLOT(setRobertsOperator()));
    connect(robertsAction, SIGNAL(triggered()),
            azone, SLOT(emitNewImage()));

    connect(aboutAction,SIGNAL(triggered()),
            about, SLOT(show()));


}

void MainWindow::configMenus()
{
    fileMenu->addAction(newFile);
    fileMenu->addAction(openFile);
    fileMenu->addAction(saveAs);

    filtersMenu->addAction(blackToWhiteAction);
    filtersMenu->addAction(negativeAction);
    filtersMenu->addAction(floydDitherAction);
    filtersMenu->addAction(orderedDitherAction);
    filtersMenu->addAction(zoomAction);
    filtersMenu->addAction(blurAction);
    filtersMenu->addAction(sharpAction);
    filtersMenu->addAction(embossAction);
    filtersMenu->addAction(waterColorAction);
    filtersMenu->addAction(gammaCorrectionAction);
    filtersMenu->addAction(sobelAction);
    filtersMenu->addAction(robertsAction);
    filtersMenu->addAction(turnAction);
    filtersMenu->addAction(runAction);

    helpMenu->addAction(aboutAction);
}

void MainWindow::handleBtoC()
{
    czone->setImageOnly(bzone->getImage());
}

void MainWindow::handleCtoB()
{
    bzone->setImageOnly(czone->getImage());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete azone;
    delete bzone;
    delete czone;
    delete mainLayout;
    delete container;
    delete scroll;
    delete mainImage;
    delete toolbar;
    delete fileMenu;
    delete filtersMenu;
    delete helpMenu;

    delete newFile;
    delete openFile;
    delete saveAs;
    delete copyBtoC;
    delete copyCtoB;
    delete blackToWhiteAction;
    delete negativeAction;
    delete floydDitherAction;
    delete robertsAction;
    delete orderedDitherAction;
    delete zoomAction;
    delete blurAction;
    delete sharpAction;
    delete embossAction;
    delete waterColorAction;
    delete gammaCorrectionAction;
    delete sobelAction;
    delete runAction;
    delete turnAction;

    delete openFileDialog;
    delete saveFileDialog;
    delete fsDitherDialog;
    delete gammaDialog;
    delete angleDialog;
    delete about;
}
