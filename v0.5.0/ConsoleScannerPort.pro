#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T21:18:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += network

#TARGET = ConsoleScannerPort
TARGET = qnetscan
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    net.cpp \
    utils.cpp \
    jthread.cpp \
    scanthread.cpp \
    app.cpp \
    console_utils.cpp

HEADERS += \
    net.h \
    utils.h \
    jthread.h \
    scanthread.h \
    app.h \
    console_utils.h
