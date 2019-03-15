#include "parametersdialog.h"

ParametersDialog::ParametersDialog(QWidget *parent) : QWidget(parent)
{
    kEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    mEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    aEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    bEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    cEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    dEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);

    kEdit->document()->setPlainText(QString::number(k));
    mEdit->document()->setPlainText(QString::number(m));
    aEdit->document()->setPlainText(QString::number(a));
    bEdit->document()->setPlainText(QString::number(b));
    cEdit->document()->setPlainText(QString::number(c));
    dEdit->document()->setPlainText(QString::number(d));

    mainLayout->addWidget(kLabel);
    mainLayout->addWidget(kEdit);
    mainLayout->addWidget(mLabel);
    mainLayout->addWidget(mEdit);
    mainLayout->addWidget(aLabel);
    mainLayout->addWidget(aEdit);
    mainLayout->addWidget(bLabel);
    mainLayout->addWidget(bEdit);
    mainLayout->addWidget(cLabel);
    mainLayout->addWidget(cEdit);
    mainLayout->addWidget(dLabel);
    mainLayout->addWidget(dEdit);
    mainLayout->addWidget(OKButton);

    connect(OKButton, SIGNAL(clicked()),
            this, SLOT(changeParams()));
    setLayout(mainLayout);
}

void ParametersDialog::changeParams()
{
    if ( kEdit->toPlainText() != "" )
    {
        k = kEdit->toPlainText().toInt();
    }
    else
    {
        kEdit->document()->setPlainText(QString::number(k));
    }

    if ( mEdit->toPlainText() != "" )
    {
        m = mEdit->toPlainText().toInt();
    }
    else
    {
        mEdit->document()->setPlainText(QString::number(m));
    }

    if ( aEdit->toPlainText() != "" )
    {
        a = aEdit->toPlainText().toFloat();
    }
    else
    {
        aEdit->document()->setPlainText(QString::number(a));
    }

    if ( bEdit->toPlainText() != "" )
    {
        b = bEdit->toPlainText().toFloat();
    }
    else
    {
        bEdit->document()->setPlainText(QString::number(b));
    }


    if ( cEdit->toPlainText() != "" )
    {
        c = cEdit->toPlainText().toFloat();
    }
    else
    {
        cEdit->document()->setPlainText(QString::number(c));
    }

    if ( dEdit->toPlainText() != "" )
    {
        d = dEdit->toPlainText().toFloat();
    }
    else
    {
        dEdit->document()->setPlainText(QString::number(d));
    }


    emit signalParamsChanged(k,m,a,b,c,d);
}

ParametersDialog::~ParametersDialog()
{
    delete kLabel;
    delete kEdit;
    delete mLabel;
    delete mEdit;
    delete aLabel;
    delete aEdit;
    delete bLabel;
    delete bEdit;
    delete cLabel;
    delete cEdit;
    delete dLabel;
    delete dEdit;
}
