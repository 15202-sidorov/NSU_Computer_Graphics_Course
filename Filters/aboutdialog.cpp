#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QWidget(parent)
{
    mainLayout->addWidget(about);
    setLayout(mainLayout);
}

AboutDialog::~AboutDialog()
{
    delete about;
    delete mainLayout;
}
