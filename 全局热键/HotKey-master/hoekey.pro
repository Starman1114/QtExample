#-------------------------------------------------
#
# Project created by QtCreator 2017-09-02T00:21:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hoekey
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    MyGlobalShortCut.cpp \
    MyWinEventFilter.cpp

HEADERS  += mainwindow.h \
    MyGlobalShortCut.h \
    MyWinEventFilter.h

FORMS    += mainwindow.ui

#这些是win系统库
LIBS += User32.LIB \
        Setupapi.lib \
        dxgi.lib \
