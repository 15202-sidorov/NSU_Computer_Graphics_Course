#ifndef ANGLEDIALOG_H
#define ANGLEDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QSlider>

class AngleDialog : public QWidget
{
    Q_OBJECT
public:
    explicit AngleDialog(QWidget *parent = nullptr);
    ~AngleDialog();

signals:
    void angleValueChanged(int angle);

public slots:
    void emitValueChanged()
    {
        int angle = angleEdit->toPlainText().toInt();
        if ( angle > MAX_ANGLE || angle < MIN_ANGLE )
        {
            return;
        }

        emit angleValueChanged(angle);
    }

    void onSliderMove(int value);

private:
    QPushButton *applyButton = new QPushButton("Apply");
    QPushButton *cancelButton = new QPushButton("Cancel");

    QPlainTextEdit *angleEdit = new QPlainTextEdit;

    QHBoxLayout *layout = new QHBoxLayout;
    QSlider *slider = new QSlider(Qt::Horizontal);

    static const int MAX_ANGLE = 360;
    static const int MIN_ANGLE = 0;
    static const int EDIT_SIZE_X = 50;
    static const int EDIT_SIZE_Y = 30;
};

#endif // ANGLEDIALOG_H
