#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>

#include "drawarea.h"
#include "colorsdisplay.h"
#include "targetfunction.h"
#include "functiondialog.h"
#include "parametersdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QScrollArea *scroll = new QScrollArea(this);
    QWidget *container = new QWidget(scroll);
    ColorsDisplay *colorDisplay = new ColorsDisplay(scroll);
    TargetFunction *function = new TargetFunction();
    Drawarea *drawArea = new Drawarea(scroll,
                                      colorDisplay,
                                      function);
    FunctionDialog *functionDialog = new FunctionDialog(this);
    ParametersDialog *paramsDialog = new ParametersDialog();
    QVBoxLayout *layout = new QVBoxLayout(scroll);
    Ui::MainWindow *ui;

    QToolBar *toolbar = new QToolBar(this);
    QAction *openDialog = new QAction(tr("&Params"),this);
    QAction *interpolate = new QAction(tr("&Interpolate"),this);
    QAction *drawIsonlines = new QAction(tr("&Isolines"),this);
    QAction *drawGrid = new QAction(tr("&Grid"),this);
};

#endif // MAINWINDOW_H
