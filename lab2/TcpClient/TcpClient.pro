#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T12:15:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++11

TARGET = TcpClient
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    nicknamedialog.cpp \
    client.cpp

HEADERS  += window.h \
    nicknamedialog.h \
    client.h

FORMS    += window.ui \
    nicknamedialog.ui
