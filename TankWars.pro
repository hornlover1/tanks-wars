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
        levelobject.cpp \
        interface.cpp \
        levelmanager.cpp \
        movablelabel.cpp

HEADERS  += mainwindow.h \
        levelobject.h \
        interface.h \
        levelmanager.h \
        movablelabel.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
