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
        createGameState.cpp \
        hierarchy.cpp \
        levelobject.cpp \
    interface.cpp

HEADERS  += mainwindow.h \
        createGameState.h \
        hierarchy.h \
        GameState.h \
        overlapLogic.h \
        levelobject.h \
    interface.h

FORMS    += mainwindow.ui
