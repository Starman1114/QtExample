#-------------------------------------------------
#
# Project created by QtCreator 2018-07-10T14:40:50
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += androidextras
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sen_MYSQL
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
    datalist.cpp \
    setdata.cpp \
    workwidget.cpp \
    countshow.cpp \
    choosensen.cpp \
    trashdialog.cpp

HEADERS += \
        widget.h \
    datalist.h \
    setdata.h \
    workwidget.h \
    countshow.h \
    choosensen.h \
    trashdialog.h

FORMS += \
        widget.ui \
    setdata.ui \
    workwidget.ui \
    countshow.ui \
    choosensen.ui \
    trashdialog.ui

CONFIG += mobility
MOBILITY = 

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

RESOURCES += \
    other/qss.qrc \
    other/main.qrc

