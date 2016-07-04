#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T14:33:07
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hopfieldnetwork.cpp \
    displaywidget.cpp

HEADERS  += mainwindow.h \
    hopfieldnetwork.h \
    displaywidget.h

FORMS    += mainwindow.ui
