#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toolbar = addToolBar("MainToolBar");
    toolbar->addAction(openDialog);
    toolbar->addAction(interpolate);
    toolbar->addAction(drawGrid);
    toolbar->addAction(drawIsonlines);

    drawGrid->setCheckable(true);
    drawIsonlines->setCheckable(true);
    interpolate->setCheckable(true);
    drawIsonlines->setChecked(true);

    layout->addWidget(functionDialog);
    layout->addWidget(drawArea);
    layout->addWidget(colorDisplay);
    colorDisplay->addColor(qRgb(255,0,0));
    colorDisplay->addColor(qRgb(255,50,0));
    colorDisplay->addColor(qRgb(255,100,0));

    colorDisplay->addColor(qRgb(255,200,0));
    colorDisplay->addColor(qRgb(255,255,0));
    colorDisplay->addColor(qRgb(255,255,100));

    colorDisplay->addColor(qRgb(0,150,200));
    colorDisplay->addColor(qRgb(0,100,200));
    colorDisplay->addColor(qRgb(0,80,200));

    function->setD(0,0,20,20);
    function->config();

    drawArea->drawFunction();
    drawArea->drawIsolines();
    connect(drawArea, SIGNAL(refreshFunctionValues(float,float,float)),
            functionDialog, SLOT(setNewValues(float,float,float)));
    connect(interpolate, SIGNAL(triggered(bool)),
            drawArea, SLOT(changeInterpolation(bool)));
    connect(drawGrid, SIGNAL(triggered(bool)),
            drawArea, SLOT(changeGrid(bool)));
    connect(drawIsonlines, SIGNAL(triggered(bool)),
            drawArea, SLOT(changeIsolines(bool)));
    connect(openDialog, SIGNAL(triggered()),
            paramsDialog, SLOT(show()));
    connect(paramsDialog,SIGNAL(signalParamsChanged(int,int,float,float,float,float)),
            drawArea, SLOT(changeParameters(int,int,float,float,float,float)));

    container->setLayout(layout);
    scroll->setWidget(container);
    setCentralWidget(scroll);
}

MainWindow::~MainWindow()
{
    delete interpolate;
    delete drawGrid;
    delete drawIsonlines;
    delete openDialog;
    delete paramsDialog;
    delete functionDialog;
    delete drawArea;
    delete colorDisplay;
    delete function;
    delete container;
    delete scroll;
    delete ui;
}
