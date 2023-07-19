#-------------------------------------------------
#
# Project created by QtCreator 2023-06-29T12:23:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spacecrafts
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    dialog.cpp \
    download.cpp \
    tableview.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    dialog.h \
    download.h \
    tableview.h

FORMS    += mainwindow.ui \
    dialog.ui \
    download.ui \
    tableview.ui
