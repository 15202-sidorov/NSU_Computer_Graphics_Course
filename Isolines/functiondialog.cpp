#include "functiondialog.h"

FunctionDialog::FunctionDialog(QWidget *parent) : QWidget(parent)
{
    functionXEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    functionYEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    functionValueEdit->setFixedSize(TEXTEDIT_SIZE_X, TEXTEDIT_SIZE_Y);
    layout->addWidget(xLabel);
    layout->addWidget(functionXEdit);
    layout->addWidget(yLabel);
    layout->addWidget(functionYEdit);
    layout->addWidget(fLabel);
    layout->addWidget(functionValueEdit);
    setLayout(layout);
}

void FunctionDialog::setNewValues( float x, float y, float value )
{
    functionXEdit->setText(QString::number(x));
    functionYEdit->setText(QString::number(y));
    functionValueEdit->setText(QString::number(value));
}

FunctionDialog::~FunctionDialog()
{
    delete xLabel;
    delete yLabel;
    delete fLabel;
    delete functionXEdit;
    delete functionYEdit;
    delete functionValueEdit;
    delete layout;
}
