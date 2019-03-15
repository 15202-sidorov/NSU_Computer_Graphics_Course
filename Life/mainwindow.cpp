#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent, FieldController *field) : QMainWindow(parent),
                                                                  ui(new Ui::MainWindow),
                                                                  field(field)
{
    ui->setupUi(this);
    createMenus();
    setActions();
    configMenus();
    toolbar = addToolBar("MainToolBar");
    fileDialog = new QFileDialog();
    saveDialog = new QFileDialog();
    aboutDialog = new AboutDialog();
    configToolbar();

    scroll = new QScrollArea(this);
    renderArea = new DrawArea(0, field);
    scroll->setWidget(renderArea);
    this->setCentralWidget(scroll);
    optionsDialog = new OptionsDialog(0,renderArea);
    setConnections();
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    modifyMenu = menuBar()->addMenu(tr("&Modify"));
    actionMenu = menuBar()->addMenu(tr("&Action"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    toolbar = new QToolBar("Maintoolbar");

    openFile = new QAction(style()->standardIcon(QStyle::SP_DirOpenIcon),tr("&Open"), this);
    saveFile = new QAction(style()->standardIcon(QStyle::SP_FileDialogStart),tr("&Save"), this);

    options = new QAction(style()->standardIcon(QStyle::SP_ComputerIcon),tr("&Options"), this);
    setReplace = new QAction(tr("&Replace"), this); //checked
    setXOR = new QAction(tr("&XOR"), this); //checked
    showImpact = new QAction(tr("&Show impact"), this); //checked

    run = new QAction(style()->standardIcon(QStyle::SP_MediaPlay),tr("&Run"), this); //checked
    next = new QAction(style()->standardIcon(QStyle::SP_ArrowRight),tr("&Next"), this);
    clear = new QAction(style()->standardIcon(QStyle::SP_DialogResetButton),tr("&Clear"),this);

    about = new QAction(style()->standardIcon(QStyle::SP_TitleBarContextHelpButton),tr("About programm"),this);
}

void MainWindow::setActions()
{
    setReplace->setCheckable(true);
    setReplace->setChecked(true);

    setXOR->setCheckable(true);
    setXOR->setChecked(false);
    setXOR->setDisabled(true);

    showImpact->setCheckable(true);
    showImpact->setChecked(false);

    run->setCheckable(true);
    run->setChecked(false);
}

void MainWindow::configMenus()
{
    fileMenu->addAction(openFile);
    fileMenu->addAction(saveFile);

    modifyMenu->addAction(options);
    modifyMenu->addAction(setReplace);
    modifyMenu->addAction(setXOR);
    modifyMenu->addAction(showImpact);

    actionMenu->addAction(run);
    actionMenu->addAction(next);
    actionMenu->addAction(clear);

    helpMenu->addAction(about);
}

void MainWindow::configToolbar()
{
    toolbar->addAction(openFile);
    toolbar->addAction(saveFile);
    toolbar->addSeparator();
    toolbar->addAction(options);
    toolbar->addAction(setReplace);
    toolbar->addAction(setXOR);
    toolbar->addAction(showImpact);
    toolbar->addSeparator();
    toolbar->addAction(run);
    toolbar->addAction(next);
    toolbar->addAction(clear);
    toolbar->addSeparator();
    toolbar->addAction(about);
}

void MainWindow::refreshDrawArea( QString filePath )
{
    FieldGetter getter(renderArea);
    getter.loadField(filePath.toStdString());
    renderArea->refreshSize();
}

void MainWindow::saveField( QString filePath )
{
    FieldWriter writer(renderArea);
    writer.loadField(filePath.toStdString());
}

void MainWindow::setConnections()
{
    connect(run,SIGNAL(triggered(bool)),renderArea, SLOT(switchRun(bool)));
    connect(next,SIGNAL(triggered(bool)), renderArea, SLOT(invokeIteration()));
    connect(clear,SIGNAL(triggered()), renderArea, SLOT(clear()));

    connect(setXOR, SIGNAL(triggered(bool)), renderArea, SLOT(setXOR(bool)));
    connect(setXOR, SIGNAL(triggered(bool)), setReplace, SLOT(setDisabled(bool)));
    connect(setReplace, SIGNAL(triggered(bool)), renderArea, SLOT(setReset(bool)));
    connect(setReplace, SIGNAL(triggered(bool)), setXOR, SLOT(setDisabled(bool)));
    connect(showImpact, SIGNAL(triggered(bool)), renderArea, SLOT(setImpactMode(bool)));

    connect(openFile, SIGNAL(triggered()), fileDialog, SLOT(open()));
    connect(saveFile, SIGNAL(triggered()), saveDialog, SLOT(open()));
    connect(fileDialog, SIGNAL(fileSelected(QString)), this, SLOT(refreshDrawArea(QString)));
    connect(saveDialog, SIGNAL(fileSelected(QString)), this, SLOT(saveField(QString)));
    connect(options, SIGNAL(triggered()), optionsDialog, SLOT(show()));
    connect(about, SIGNAL(triggered()), aboutDialog, SLOT(show()));
}


MainWindow::~MainWindow()
{
    delete toolbar;
    delete openFile;
    delete saveFile;
    delete options;
    delete setReplace;
    delete setXOR;
    delete showImpact;
    delete run;
    delete next;
    delete clear;
    delete about;
    delete ui;
    delete renderArea;
    delete field;
    delete fileDialog;
    delete saveDialog;
    delete optionsDialog;
    delete aboutDialog;
    std::cout << "Delete" << std::endl;
}

