#include "optionsdialog.h"

#include <iostream>

OptionsDialog::OptionsDialog( QWidget *parent, DrawArea *drawArea ) :
    QWidget(parent), drawArea(drawArea)
{
    fieldCtl = drawArea->getField();
    rowsEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    columnsEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    cellSizeEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    timerEdit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    FST_IMPACT_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    SND_IMPACT_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    LIFE_BEGIN_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    LIFE_END_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    BIRTH_BEGIN_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);
    BIRTH_END_Edit->setFixedSize(EDIT_SIZE_X, EDIT_SIZE_Y);

    rowsSlider->setRange(ROW_MIN, ROW_MAX);
    columnsSlider->setRange(COLUMN_MIN, COLUMN_MAX);
    cellSizeSlider->setRange(CELL_SIZE_MIN, CELL_SIZE_MAX);
    timerSlider->setRange(TIMER_MIN, TIMER_MAX);

    fieldOptionsLayout->addWidget(rowLabel);
    fieldOptionsLayout->addWidget(rowsEdit);
    fieldOptionsLayout->addWidget(rowsSlider);
    fieldOptionsLayout->addWidget(columnLabel);
    fieldOptionsLayout->addWidget(columnsEdit);
    fieldOptionsLayout->addWidget(columnsSlider);
    fieldOptionsLayout->addWidget(cellSizeLabel);
    fieldOptionsLayout->addWidget(cellSizeEdit);
    fieldOptionsLayout->addWidget(cellSizeSlider);
    fieldOptionsLayout->addWidget(timerLabel);
    fieldOptionsLayout->addWidget(timerEdit);
    fieldOptionsLayout->addWidget(timerSlider);

    modeOptionsLayout->addWidget(XORCheckBox);
    modeOptionsLayout->addWidget(XORLabel);
    modeOptionsLayout->addWidget(replaceCheckBox);
    modeOptionsLayout->addWidget(replaceLabel);

    impactOptionsLayout->addWidget(FST_IMPACT_Label);
    impactOptionsLayout->addWidget(FST_IMPACT_Edit);
    impactOptionsLayout->addWidget(SND_IMPACT_Label);
    impactOptionsLayout->addWidget(SND_IMPACT_Edit);

    environmentOptionsLayout->addWidget(LIFE_BEGIN_Label);
    environmentOptionsLayout->addWidget(LIFE_BEGIN_Edit);
    environmentOptionsLayout->addWidget(LIFE_END_Label);
    environmentOptionsLayout->addWidget(LIFE_END_Edit);
    environmentOptionsLayout->addWidget(BIRTH_BEGIN_Label);
    environmentOptionsLayout->addWidget(BIRTH_BEGIN_Edit);
    environmentOptionsLayout->addWidget(BIRTH_END_Label);
    environmentOptionsLayout->addWidget(BIRTH_END_Edit);

    dialogLayout->addLayout(fieldOptionsLayout, 0, 0);
    dialogLayout->addLayout(modeOptionsLayout, 1, 0);
    dialogLayout->addLayout(impactOptionsLayout, 1 ,1);
    dialogLayout->addLayout(environmentOptionsLayout,0,1);
    dialogLayout->addWidget(okButton);
    dialogLayout->addWidget(cancelButton);

    setLayout(dialogLayout);

    rowsSlider->setValue(fieldCtl->getHeight());
    updateTextOnRowEdit(fieldCtl->getHeight());
    columnsSlider->setValue(fieldCtl->getWidth());
    updateTextOnColumnEdit(fieldCtl->getWidth());
    cellSizeSlider->setValue(drawArea->getPoligonSize());
    updateTextOnCellSizeEdit(drawArea->getPoligonSize());
    timerSlider->setValue(drawArea->getTimerInterval());
    updateTextOnTimerEdit(drawArea->getTimerInterval());

    updateTextOnSliderChange(FST_IMPACT_Edit, fieldCtl->getFstImpact());
    updateTextOnSliderChange(SND_IMPACT_Edit, fieldCtl->getScdImpact());
    updateTextOnSliderChange(LIFE_BEGIN_Edit, fieldCtl->getLifeBegin());
    updateTextOnSliderChange(LIFE_END_Edit,   fieldCtl->getLifeEnd());
    updateTextOnSliderChange(BIRTH_BEGIN_Edit,fieldCtl->getBirthBegin());
    updateTextOnSliderChange(BIRTH_END_Edit,  fieldCtl->getBirthEnd());
    if ( !drawArea->getRegime() )
    {
        replaceCheckBox->setChecked(1);
        switchToReplace(1);
    }
    else {
        XORCheckBox->setChecked(1);
        switchToXor(1);
    }

    setConnections();
}

void OptionsDialog::updateTextOnSliderChange( QPlainTextEdit *target,  int value )
{
    target->setPlainText(QString::number(value));
}

void OptionsDialog::updateTextOnSliderChange( QPlainTextEdit *target,  float value )
{
    target->setPlainText(QString::number(value));
}

void OptionsDialog::updateTextOnRowEdit( int value )
{
    updateTextOnSliderChange(rowsEdit,value);
}

void OptionsDialog::updateTextOnColumnEdit( int value )
{
    updateTextOnSliderChange(columnsEdit, value);
}

void OptionsDialog::updateTextOnCellSizeEdit( int value )
{
    updateTextOnSliderChange(cellSizeEdit, value);
}

void OptionsDialog::updateTextOnTimerEdit( int value )
{
    updateTextOnSliderChange(timerEdit, value);
}

void OptionsDialog::switchToXor( bool state )
{
    if ( state )
    {
        replaceCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }
    else
    {
        replaceCheckBox->setCheckState(Qt::CheckState::Checked);
    }
}

void OptionsDialog::switchToReplace( bool state )
{
    if ( state )
    {
        XORCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }
    else
    {
        XORCheckBox->setCheckState(Qt::CheckState::Checked);
    }
}

void OptionsDialog::closingOK()
{
    fieldCtl->resize(columnsEdit->toPlainText().toInt(),
                     rowsEdit->toPlainText().toInt());
    if ( replaceCheckBox->isChecked() )
    {
        drawArea->setReset(1);
    }
    else
    {
        drawArea->setXOR(1);
    }

    if ( cellSizeEdit->toPlainText().toInt() > CELL_SIZE_MAX )
    {
        cellSizeEdit->setPlainText(QString::number(CELL_SIZE_MAX));
    }

    if ( cellSizeEdit->toPlainText().toInt() < CELL_SIZE_MIN )
    {
        cellSizeEdit->setPlainText(QString::number(CELL_SIZE_MIN));
    }

    if ( timerEdit->toPlainText().toInt() < TIMER_MIN )
    {
        timerEdit->setPlainText(QString::number(TIMER_MIN));
    }

    if ( timerEdit->toPlainText().toInt() > TIMER_MAX )
    {
        timerEdit->setPlainText(QString::number(TIMER_MAX));
    }

    drawArea->newPoligonSize(cellSizeEdit->toPlainText().toInt());
    drawArea->setTimerInterval(timerEdit->toPlainText().toInt());

    fieldCtl->setLifeBegin(LIFE_BEGIN_Edit->toPlainText().toFloat());
    fieldCtl->setLifeEnd(LIFE_END_Edit->toPlainText().toFloat());
    fieldCtl->setBrithBegin(BIRTH_BEGIN_Edit->toPlainText().toFloat());
    fieldCtl->setBirthEnd(BIRTH_END_Edit->toPlainText().toFloat());
    fieldCtl->setFstImpact(FST_IMPACT_Edit->toPlainText().toFloat());
    fieldCtl->setScdImpact(SND_IMPACT_Edit->toPlainText().toFloat());

    drawArea->refreshSize();
    close();
}

void OptionsDialog::closingCANCEL()
{
    close();
}

void OptionsDialog::setConnections()
{
    connect(rowsSlider, SIGNAL(valueChanged(int)), this, SLOT(updateTextOnRowEdit(int)));
    connect(columnsSlider, SIGNAL(valueChanged(int)), this, SLOT(updateTextOnColumnEdit(int)));
    connect(cellSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateTextOnCellSizeEdit(int)));
    connect(timerSlider, SIGNAL(valueChanged(int)), this, SLOT(updateTextOnTimerEdit(int)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(closingOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(closingCANCEL()));
    connect(XORCheckBox, SIGNAL(clicked(bool)), this, SLOT(switchToXor(bool)));
    connect(replaceCheckBox, SIGNAL(clicked(bool)), this, SLOT(switchToReplace(bool)));
}

OptionsDialog::~OptionsDialog()
{
    delete rowLabel;
    delete columnLabel;
    delete cellSizeLabel;
    delete timerLabel;

    delete FST_IMPACT_Label;
    delete SND_IMPACT_Label;
    delete XORLabel;
    delete replaceLabel;

    delete XORCheckBox;
    delete replaceCheckBox;

    delete rowsSlider;
    delete columnsSlider;
    delete cellSizeSlider;
    delete timerSlider;

    delete rowsEdit;
    delete columnsEdit;
    delete cellSizeEdit;
    delete timerEdit;
    delete FST_IMPACT_Edit;
    delete SND_IMPACT_Edit;
    delete LIFE_BEGIN_Edit;
    delete LIFE_END_Edit;
    delete BIRTH_BEGIN_Edit;
    delete BIRTH_END_Edit;


    delete okButton;
    delete cancelButton;

    delete environmentOptionsLayout;
    delete impactOptionsLayout;
    delete modeOptionsLayout;
    delete fieldOptionsLayout;
    delete dialogLayout;
    std::cout << "Delete" << std::endl;
}
