#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QToolButton>
#include <QFileDialog>

#include "optionsdialog.h"
#include "drawarea.h"
#include "fieldgetter.h"
#include "fieldwriter.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, FieldController *field = 0);

    inline DrawArea *getDrawArea() { return renderArea; }

    ~MainWindow();
public slots:
    void refreshDrawArea (QString filePath);
    void saveField (QString filePath);

private:
    Ui::MainWindow  *ui;
    DrawArea *renderArea;
    FieldController *field;
    FieldGetter *getter;

    QScrollArea *scroll;

    void setActions();
    void configMenus();
    void configToolbar();
    void createMenus();
    void setConnections();

    OptionsDialog *optionsDialog;
    AboutDialog *aboutDialog;
    QFileDialog *fileDialog;
    QFileDialog *saveDialog;
    QToolBar *toolbar;

    QMenu *fileMenu;
    QMenu *modifyMenu;
    QMenu *actionMenu;
    QMenu *helpMenu;

    QAction *newFile;
    QAction *openFile;
    QAction *saveFile;

    QAction *options;
    QAction *setReplace;
    QAction *setXOR;
    QAction *showImpact;

    QAction *run;
    QAction *next;
    QAction *clear;

    QAction *about;


};

#endif // MAINWINDOW_H
