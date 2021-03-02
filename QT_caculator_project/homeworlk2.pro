#-------------------------------------------------
#
# Project created by QtCreator 2020-12-11T18:22:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = caculater
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    caculate.cpp

HEADERS  += dialog.h \
    caculate.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
