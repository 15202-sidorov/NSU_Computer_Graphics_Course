#ifndef FSDITHERDIALOG_H
#define FSDITHERDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>

class FSDitherDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FSDitherDialog(QWidget *parent = nullptr);

signals:
    void valuesUpdated(int redN,
                       int greenN,
                       int blueN);

public slots:
    inline void emitValuesUpdated()
    {
        int redN = redEdit->toPlainText().toInt();
        int greenN = greenEdit->toPlainText().toInt();
        int blueN = blueEdit->toPlainText().toInt();
        emit valuesUpdated(redN, greenN, blueN);
    }

private:

    QLabel *redLabel = new QLabel("RedN");
    QLabel *greenLabel = new QLabel("GreenN");
    QLabel *blueLabel = new QLabel("BlueN");

    QPlainTextEdit *redEdit = new QPlainTextEdit;
    QPlainTextEdit *greenEdit = new QPlainTextEdit;
    QPlainTextEdit *blueEdit = new QPlainTextEdit;

    QPushButton *applyButton = new QPushButton("Apply");

    QHBoxLayout *layout = new QHBoxLayout();

    static const int EDIT_SIZE_X = 50;
    static const int EDIT_SIZE_Y = 30;
};

#endif // FSDITHERDIALOG_H
