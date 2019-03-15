#ifndef GAMMADIALOG_H
#define GAMMADIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QPlainTextEdit>
#include <QHBoxLayout>

class GammaDialog : public QWidget
{
    Q_OBJECT
public:
    explicit GammaDialog(QWidget *parent = nullptr);
    ~GammaDialog();

signals:
    void gammaValueChanged(float gamma);

public slots:
    void emitValueChanged()
    {
        float gamma = gammaEdit->toPlainText().toFloat();
        if ( gamma > MAX_GAMMA || gamma < MIN_GAMMA )
        {
            return;
        }

        emit gammaValueChanged(gamma);
    }

private:
    QPushButton *applyButton = new QPushButton("Aplly");
    QPushButton *cancelButton = new QPushButton("Cancel");

    QPlainTextEdit *gammaEdit = new QPlainTextEdit;

    QHBoxLayout *layout = new QHBoxLayout;


    static const int MAX_GAMMA = 10;
    static const int MIN_GAMMA = 1;
    static const int EDIT_SIZE_X = 50;
    static const int EDIT_SIZE_Y = 30;

};

#endif // GAMMADIALOG_H
