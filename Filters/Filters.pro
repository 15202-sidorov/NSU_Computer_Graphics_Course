#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T15:35:02
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filters
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        rawimage.cpp \
    azone.cpp \
    bzone.cpp \
    czone.cpp \
    zone.cpp \
    doublepicture.cpp \
    filter.cpp \
    grayscalecolor.cpp \
    negativecolor.cpp \
    fsdithering.cpp \
    blurfilter.cpp \
    sobeloperator.cpp \
    ordereddither.cpp \
    aquerellfilter.cpp \
    sharpfilter.cpp \
    embosefilter.cpp \
    gammafilter.cpp \
    fsditherdialog.cpp \
    gammadialog.cpp \
    robertsfilter.cpp \
    turningfilter.cpp \
    aboutdialog.cpp \
    angledialog.cpp

HEADERS += \
        mainwindow.h \
        rawimage.h \
    azone.h \
    bzone.h \
    czone.h \
    zone.h \
    doublepicture.h \
    filter.h \
    grayscalecolor.h \
    negativecolor.h \
    fsdithering.h \
    blurfilter.h \
    sobeloperator.h \
    ordereddither.h \
    aquerellfilter.h \
    sharpfilter.h \
    embosefilter.h \
    gammafilter.h \
    fsditherdialog.h \
    gammadialog.h \
    robertsfilter.h \
    turningfilter.h \
    aboutdialog.h \
    angledialog.h

FORMS += \
        mainwindow.ui
