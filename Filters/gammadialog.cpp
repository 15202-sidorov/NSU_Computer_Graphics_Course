#include "gammadialog.h"

GammaDialog::GammaDialog(QWidget *parent) : QWidget(parent)
{
    gammaEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    layout->addWidget(gammaEdit);
    layout->addWidget(applyButton);
    layout->addWidget(cancelButton);
    setLayout(layout);

    connect(applyButton, SIGNAL(clicked()), this, SLOT(emitValueChanged()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

GammaDialog::~GammaDialog()
{
    delete applyButton;
    delete cancelButton;
    delete gammaEdit;
    delete layout;
}
