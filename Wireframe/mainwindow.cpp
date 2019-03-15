#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rotateFigureButton->setCheckable(true);

    kEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    nEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    mEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    aEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    bEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    cEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    dEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    rEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    gEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    blEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    shEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    swEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    znEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    zfEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);

    buttonsLayout->addWidget(nextFigureButton);
    buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(newFigureButton);
    buttonsLayout->addWidget(deleteFigureButton);
    buttonsLayout->addWidget(rotateFigureButton);
    optionsLayout->addWidget(nLabel, 0, 0);
    optionsLayout->addWidget(mLabel, 1, 0);
    optionsLayout->addWidget(kLabel, 2, 0);
    optionsLayout->addWidget(nEdit,  0, 1);
    optionsLayout->addWidget(mEdit,  1, 1);
    optionsLayout->addWidget(kEdit,  2, 1);

    optionsLayout->addWidget(aLabel, 0, 2);
    optionsLayout->addWidget(bLabel, 1, 2);
    optionsLayout->addWidget(cLabel, 2, 2);
    optionsLayout->addWidget(dLabel, 3, 2);
    optionsLayout->addWidget(aEdit,  0, 3);
    optionsLayout->addWidget(bEdit,  1, 3);
    optionsLayout->addWidget(cEdit,  2, 3);
    optionsLayout->addWidget(dEdit,  3, 3);

    optionsLayout->addWidget(swLabel, 0, 4);
    optionsLayout->addWidget(shLabel, 1, 4);
    optionsLayout->addWidget(znLabel, 2, 4);
    optionsLayout->addWidget(zfLabel, 3, 4);
    optionsLayout->addWidget(swEdit,  0, 5);
    optionsLayout->addWidget(shEdit,  1, 5);
    optionsLayout->addWidget(znEdit,  2, 5);
    optionsLayout->addWidget(zfEdit,  3, 5);

    optionsLayout->addWidget(rLabel, 0, 6);
    optionsLayout->addWidget(gLabel, 1, 6);
    optionsLayout->addWidget(blLabel, 2, 6);
    optionsLayout->addWidget(rEdit,  0, 7);
    optionsLayout->addWidget(gEdit,  1, 7);
    optionsLayout->addWidget(blEdit,  2, 7);

    figure->addFigure(new Figure3D(this, new SplineEdit()));
    currentFigure = figure->getFigure(0);
    setEdits();

    splinesLayout->addWidget(currentFigure->getSpline());

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(figureLabel);
    mainLayout->addLayout(splinesLayout);
    mainLayout->addLayout(optionsLayout);
    figure->show();
    container->setLayout(mainLayout);
    scroll->setWidget(container);
    setCentralWidget(scroll);

    QWidget::connect(nextFigureButton, SIGNAL(clicked()),
                     this, SLOT(setNextFigure()));
    QWidget::connect(applyButton, SIGNAL(clicked()),
                     this, SLOT(applyChanges()));
    QWidget::connect(newFigureButton, SIGNAL(clicked()),
                     this, SLOT(createFigure()));
    QWidget::connect(deleteFigureButton, SIGNAL(clicked()),
                     this, SLOT(deleteCurrentFigure()));
    QWidget::connect(figure->getCamera(), SIGNAL(znChanged(float,float)),
                     this, SLOT(setZn(float,float)));
    QWidget::connect(rotateFigureButton,SIGNAL(clicked(bool)),
                     this, SLOT(setFigureRotateMode(bool)));
}

void MainWindow::setFigureRotateMode( bool isOn )
{
    if ( isOn )
    {
        figure->displayOneOnly(currentFigureIndex);
    }
    else
    {
        figure->displayAll();
    }
}

void MainWindow::setZn( float zn, float zf )
{
    znEdit->setText(QString::number(zn));
    zfEdit->setText(QString::number(zf));
}

void MainWindow::createFigure()
{
    figure->addFigure(new Figure3D(this,new SplineEdit()));
    currentFigure->getSpline()->hide();
    currentFigureIndex = figure->figuresCount() - 1;
    currentFigure = figure->getFigure(currentFigureIndex);
    splinesLayout->addWidget(currentFigure->getSpline());
    setEdits();
    figureLabel->setText("Figure " + QString::number(currentFigureIndex));
}

void MainWindow::setNextFigure()
{
    currentFigure->getSpline()->hide();
    currentFigureIndex++;
    currentFigureIndex %= figure->figuresCount();
    currentFigure = figure->getFigure(currentFigureIndex);
    currentFigure->getSpline()->setHidden(false);
    setEdits();
    figureLabel->setText("Figure " + QString::number(currentFigureIndex));
}

void MainWindow::deleteCurrentFigure()
{
    figure->deleteFigure(currentFigureIndex);
    currentFigureIndex %= figure->figuresCount();
    currentFigure = figure->getFigure(currentFigureIndex);
    currentFigure->getSpline()->setHidden(false);
    setEdits();
    figureLabel->setText("Figure " + QString::number(currentFigureIndex));
}

void MainWindow::applyChanges()
{
    currentFigure->setN(nEdit->text().toInt());
    currentFigure->setM(mEdit->text().toInt());
    currentFigure->setK(kEdit->text().toInt());

    currentFigure->setA(aEdit->text().toFloat());
    currentFigure->setB(bEdit->text().toFloat());
    currentFigure->setC(cEdit->text().toFloat());
    currentFigure->setD(dEdit->text().toFloat());

    currentFigure->setColor(rEdit->text().toInt(),
                            gEdit->text().toInt(),
                            blEdit->text().toInt());

    Camera *figureCam = figure->getCamera();
    figureCam->setWidth(swEdit->text().toFloat());
    figureCam->setHeight(shEdit->text().toFloat());
    figureCam->setZn(znEdit->text().toFloat());
    figureCam->setZf(zfEdit->text().toFloat());

    currentFigure->buildFigure();
    figure->drawProjection();
}

void MainWindow::setEdits()
{
    nEdit->setText(QString::number(currentFigure->getN()));
    mEdit->setText(QString::number(currentFigure->getM()));
    kEdit->setText(QString::number(currentFigure->getK()));

    aEdit->setText(QString::number(currentFigure->getA()));
    bEdit->setText(QString::number(currentFigure->getB()));
    cEdit->setText(QString::number(currentFigure->getC()));
    dEdit->setText(QString::number(currentFigure->getD()));

    swEdit->setText(QString::number(figure->getCamera()->getWidth()));
    shEdit->setText(QString::number(figure->getCamera()->getHeight()));
    znEdit->setText(QString::number(figure->getCamera()->getZn()));
    zfEdit->setText(QString::number(figure->getCamera()->getZf()));

    QColor figureColor = currentFigure->getColor();
    rEdit->setText(QString::number(figureColor.red()));
    gEdit->setText(QString::number(figureColor.green()));
    blEdit->setText(QString::number(figureColor.blue()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete figureLabel;
    delete kLabel;  delete kEdit;
    delete nLabel;  delete nEdit;
    delete mLabel;  delete mEdit;
    delete aLabel;  delete aEdit;
    delete bLabel;  delete bEdit;
    delete cLabel;  delete cEdit;
    delete dLabel;  delete dEdit;
    delete rLabel;  delete rEdit;
    delete gLabel;  delete gEdit;
    delete blLabel; delete blEdit;
    delete shLabel; delete shEdit;
    delete swLabel; delete swEdit;
    delete znLabel; delete znEdit;
    delete zfLabel; delete zfEdit;


    delete nextFigureButton;
    delete newFigureButton;
    delete deleteFigureButton;
    delete rotateFigureButton;
    delete applyButton;

    delete optionsLayout;
    delete buttonsLayout;

    delete figure;
}
