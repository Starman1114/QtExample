#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T15:32:06
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += network
QT       += androidextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicSend
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
        widget.cpp \
    workerthread.cpp \
    datalist.cpp \
    monitor.cpp \
    Downchirp/Downchirp.cpp \
    Downchirp/Downchirp_initialize.cpp \
    Downchirp/Downchirp_terminate.cpp \
    Upchirp/rt_nonfinite.cpp \
    Upchirp/rtGetInf.cpp \
    Upchirp/rtGetNaN.cpp \
    Upchirp/Upchirp.cpp \
    Upchirp/Upchirp_initialize.cpp \
    Upchirp/Upchirp_terminate.cpp

HEADERS += \
        widget.h \
    workerthread.h \
    datalist.h \
    monitor.h \
    Downchirp/Downchirp.h \
    Downchirp/Downchirp_initialize.h \
    Downchirp/Downchirp_terminate.h \
    Downchirp/Downchirp_types.h \
    Upchirp/rt_nonfinite.h \
    Upchirp/rtGetInf.h \
    Upchirp/rtGetNaN.h \
    Upchirp/rtwtypes.h \
    Upchirp/Upchirp.h \
    Upchirp/Upchirp_initialize.h \
    Upchirp/Upchirp_terminate.h \
    Upchirp/Upchirp_types.h


FORMS += \
        widget.ui \


CONFIG += mobility
MOBILITY = 

RESOURCES += \
    other/main.qrc \
    other/qss.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/qtproject/example/MainActivity.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

