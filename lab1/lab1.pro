#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T13:15:36
#
#-------------------------------------------------

QT       += core

QT       += gui

QT       += widgets opengl

QT       += sql

CONFIG += C++11 console

SOURCES += main.cpp \
    openglwidget.cpp \
    object.cpp \
    camera.cpp \
    mainwindow.cpp \
    dialogproperties.cpp \
    axis.cpp \
    database.cpp

HEADERS += \
    openglwidget.h \
    object.h \
    camera.h \
    mainwindow.h \
    dialogproperties.h \
    axis.h \
    database.h

DISTFILES += \
    object.vert \
    object.frag \
    objectNumber.frag \
    objectNumber.vert \
    axis.frag \
    axis.vert

FORMS += \
    mainwindow.ui \
    dialogproperties.ui
