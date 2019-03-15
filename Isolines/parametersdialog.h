#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class ParametersDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersDialog(QWidget *parent = nullptr);
    ~ParametersDialog();
signals:
    void signalParamsChanged(int k, int m,
                             float a, float b,
                             float c, float d);

public slots:
    void changeParams();

private:
    static const int EDIT_SIZE_X = 50;
    static const int EDIT_SIZE_Y = 30;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *kLabel = new QLabel("K : ");
    QLabel *mLabel = new QLabel("M : ");
    QLabel *aLabel = new QLabel("A : ");
    QLabel *bLabel = new QLabel("B : ");
    QLabel *cLabel = new QLabel("C : ");
    QLabel *dLabel = new QLabel("D : ");

    QPlainTextEdit *kEdit = new QPlainTextEdit;
    QPlainTextEdit *mEdit = new QPlainTextEdit;
    QPlainTextEdit *aEdit = new QPlainTextEdit;
    QPlainTextEdit *bEdit = new QPlainTextEdit;
    QPlainTextEdit *cEdit = new QPlainTextEdit;
    QPlainTextEdit *dEdit = new QPlainTextEdit;

    QPushButton *OKButton = new QPushButton("OK");

    int k = 10;
    int m = 10;
    float a = 0;
    float b = 20;
    float c = 0;
    float d = 20;

};

#endif // PARAMETERSDIALOG_H
