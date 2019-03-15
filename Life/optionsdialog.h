#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QPlainTextEdit>
#include <QCheckBox>

#include "drawarea.h"
#include "fieldcontroller.h"


class OptionsDialog : public QWidget
{
    Q_OBJECT
    /*
        Define staring parameters from fieldCtl or something.
        Bind Main window and drawarea.
        Make field writer and bind it with main window.
        Check out field controller mistake.
    */
public:
    explicit OptionsDialog(QWidget *parent = nullptr,
                           DrawArea *drawArea = nullptr);
    ~OptionsDialog();

signals:

public slots:
    void updateTextOnRowEdit      (int value);
    void updateTextOnColumnEdit   (int value);
    void updateTextOnCellSizeEdit (int value);
    void updateTextOnTimerEdit    (int value);
    void closingOK                ();
    void closingCANCEL            ();
    void switchToXor              (bool state);
    void switchToReplace          (bool state);

private:
    void setConnections();
    void updateTextOnSliderChange (QPlainTextEdit *target, int   value);
    void updateTextOnSliderChange (QPlainTextEdit *target, float value);

    DrawArea * drawArea;
    FieldController * fieldCtl;

    QLabel *rowLabel = new QLabel("Rows");
    QLabel *columnLabel = new QLabel("Columns");
    QLabel *cellSizeLabel = new QLabel("Cell Size");
    QLabel *timerLabel = new QLabel("Timer interval");

    QLabel *FST_IMPACT_Label = new QLabel("FST_IMPACT");
    QLabel *SND_IMPACT_Label = new QLabel("SND_IMPACT");

    QLabel *LIFE_BEGIN_Label = new QLabel("LIFE_BEGIN");
    QLabel *LIFE_END_Label = new QLabel("LIFE_END");
    QLabel *BIRTH_BEGIN_Label = new QLabel("BIRTH_BEGIN");
    QLabel *BIRTH_END_Label = new QLabel("BIRTH_END");

    QLabel *XORLabel = new QLabel("XOR");
    QLabel *replaceLabel = new QLabel("Replace");

    QCheckBox *XORCheckBox = new QCheckBox;
    QCheckBox *replaceCheckBox = new QCheckBox;

    QGridLayout *dialogLayout = new QGridLayout(this);
    QVBoxLayout *fieldOptionsLayout = new QVBoxLayout();
    QHBoxLayout *modeOptionsLayout = new QHBoxLayout();
    QVBoxLayout *impactOptionsLayout = new QVBoxLayout();
    QVBoxLayout *environmentOptionsLayout = new QVBoxLayout();

    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    QSlider *rowsSlider = new QSlider(Qt::Horizontal);
    QSlider *columnsSlider = new QSlider(Qt::Horizontal);
    QSlider *cellSizeSlider = new QSlider(Qt::Horizontal);
    QSlider *timerSlider = new QSlider(Qt::Horizontal);

    QPlainTextEdit *rowsEdit = new QPlainTextEdit;
    QPlainTextEdit *columnsEdit = new QPlainTextEdit;
    QPlainTextEdit *cellSizeEdit = new QPlainTextEdit;
    QPlainTextEdit *timerEdit = new QPlainTextEdit;

    QPlainTextEdit *FST_IMPACT_Edit = new QPlainTextEdit;
    QPlainTextEdit *SND_IMPACT_Edit = new QPlainTextEdit;

    QPlainTextEdit *LIFE_BEGIN_Edit = new QPlainTextEdit;
    QPlainTextEdit *LIFE_END_Edit = new QPlainTextEdit;
    QPlainTextEdit *BIRTH_BEGIN_Edit = new QPlainTextEdit;
    QPlainTextEdit *BIRTH_END_Edit = new QPlainTextEdit;

    static const int EDIT_SIZE_X = 50;
    static const int EDIT_SIZE_Y = 30;

    static const int ROW_MAX = 100;
    static const int ROW_MIN = 2;
    static const int COLUMN_MAX = 100;
    static const int COLUMN_MIN = 2;
    static const int CELL_SIZE_MIN = 25;
    static const int CELL_SIZE_MAX = 150;
    static const int TIMER_MIN = 1;
    static const int TIMER_MAX = 1000;

};

#endif // OPTIONSDIALOG_H
