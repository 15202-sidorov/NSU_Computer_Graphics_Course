#include "angledialog.h"

AngleDialog::AngleDialog(QWidget *parent) : QWidget(parent)
{
    slider->setRange(MIN_ANGLE,MAX_ANGLE);

    angleEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    layout->addWidget(angleEdit);
    layout->addWidget(slider);
    layout->addWidget(applyButton);
    layout->addWidget(cancelButton);
    setLayout(layout);

    connect(applyButton, SIGNAL(clicked()),
            this, SLOT(emitValueChanged()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(slider, SIGNAL(valueChanged(int)),
            this, SLOT(onSliderMove(int)));

}

void AngleDialog::onSliderMove( int value )
{
    angleEdit->setPlainText(QString::number(value));
}

AngleDialog::~AngleDialog()
{
    delete applyButton;
    delete cancelButton;
    delete angleEdit;
    delete slider;
    delete layout;
}
