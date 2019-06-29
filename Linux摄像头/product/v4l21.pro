#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T14:25:46
#
#-------------------------------------------------
CONFIG   += console
QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = v4l21
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    v4l2.cpp \
    camera_thread.cpp \
    form.cpp \
    path.cpp \
    qtserial.cpp

HEADERS  += mainwindow.h \
    v4l2.h \
    camera_thread.h \
    form.h \
    path.h \
    qtserial.h

FORMS    += mainwindow.ui \
    form.ui \
    path.ui \
    qtserial.ui
