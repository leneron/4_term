QT += core
QT += network

CONFIG += C++11

TARGET = TcpServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainserver.cpp \
    serverclient.cpp

HEADERS += \
    mainserver.h \
    serverclient.h
