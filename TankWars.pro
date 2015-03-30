#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T15:27:00
#
#-------------------------------------------------

QT       += core gui network

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
    networkmanager.cpp

HEADERS  += mainwindow.h \
        levelobject.h \
        interface.h \
        levelmanager.h \
        movablelabel.h \
    unittests.h \
    opponentmanager.h \
    networkmanager.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

QT += multimedia

RESOURCES += \
    resources.qrc
