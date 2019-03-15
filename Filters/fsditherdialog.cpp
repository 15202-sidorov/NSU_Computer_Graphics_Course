#include "fsditherdialog.h"

FSDitherDialog::FSDitherDialog(QWidget *parent) : QWidget(parent)
{
    redEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    greenEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    blueEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);

    layout->addWidget(redLabel);
    layout->addWidget(redEdit);
    layout->addWidget(greenLabel);
    layout->addWidget(greenEdit);
    layout->addWidget(blueLabel);
    layout->addWidget(blueEdit);
    layout->addWidget(applyButton);

    setLayout(layout);

    connect(applyButton, SIGNAL(clicked()), this, SLOT(emitValuesUpdated()));
}
