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
        movablelabel.cpp \
    unittests.cpp \
    opponentmanager.cpp \
    mastertimer.cpp

HEADERS  += mainwindow.h \
        levelobject.h \
        interface.h \
        levelmanager.h \
        movablelabel.h \
    unittests.h \
    opponentmanager.h \
    mastertimer.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    resources.qrc
