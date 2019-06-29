#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T09:03:09
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += widgets
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pybsystem
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
        dialog.cpp \
    iconhelper.cpp \
    datachange.cpp \
    datalist.cpp \
    function.cpp \
    functiondata.cpp \
    JY901.cpp \
    mathw.cpp \
    record.cpp \
    setpath.cpp \
    workerthread.cpp \
    chart.cpp \
    countstep.cpp \
    Com.cpp \
    count.cpp \
    gait.cpp \
    gaitcount.cpp


HEADERS += \
        dialog.h \
    iconhelper.h \
    chart.h \
    Com.h \
    countstep.h \
    datachange.h \
    datalist.h \
    function.h \
    functiondata.h \
    JY901.h \
    mathw.h \
    record.h \
    setpath.h \
    workerthread.h \
    count.h \
    gait.h \
    gaitcount.h


FORMS += \
        dialog.ui \
    countstep.ui \
    function.ui \
    mathw.ui \
    setpath.ui \
    gaitcount.ui


SUBDIRS += \
    Project.pro \
    pybsystem.pro \
    pybsystem.pro

DISTFILES += \
    Project.pro.user

RESOURCES += \
    other/main.qrc \
    other/qss.qrc
