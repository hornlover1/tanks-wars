#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T15:27:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankWars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        levelobject.h \
        interface.cpp \
        levelmanager.cpp

HEADERS  += mainwindow.h \
        levelobject.h \
        interface.h \
        levelmanager.h

FORMS    += mainwindow.ui
