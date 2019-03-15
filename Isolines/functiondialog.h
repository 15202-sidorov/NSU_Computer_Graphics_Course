#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>

class FunctionDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionDialog(QWidget *parent = nullptr);
    ~FunctionDialog();

public slots:
    void setNewValues(float x, float y, float value);

private:
    QLabel *xLabel = new QLabel("x : ");
    QLabel *yLabel = new QLabel("y : ");
    QLabel *fLabel = new QLabel("f(x,y) :");

    QLabel *functionValueEdit = new QLabel;
    QLabel *functionXEdit = new QLabel;
    QLabel *functionYEdit = new QLabel;

    QHBoxLayout *layout = new QHBoxLayout(this);
    static const int TEXTEDIT_SIZE_X = 60;
    static const int TEXTEDIT_SIZE_Y = 40;

};

#endif // FUNCTIONDIALOG_H
