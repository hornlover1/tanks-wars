//--------------------------------------------------------------
// File:   interface.h
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains the singleton for the interface,
//      the psuedo observer that connects the model to the view
//      and updates the gui.
//--------------------------------------------------------------

#ifndef INTERFACE_H
#define INTERFACE_H

#include "levelobject.h"
#include "movablelabel.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QString>

class Interface {
    Interface();
    static Interface instance;
    static Ui::MainWindow* ui;

    void updateGUI();
    void updateFiles();
public:
    //singleton class
    static Interface getInstance();

    //set the ui element for use in manipulating stuff on the screen
    static void setUi(Ui::MainWindow* initUi);

    //draw the object on the screen
    void drawObject(LevelObject* obj);

    //returns the time remaining as an int, so we can add the highscore
    int getTimeLeft();

    //move the object around on the screen
    void moveObject(LevelObject* obj);

    //take the object representing the LevelObject off the screen
    void deleteObject(LevelObject* obj);

    //shows the current time on the gui
    void showTime(QString);

    //shows the victory message when the user wins.
    void showVictory();

    //displays the instructions to the game
    void howTo();

    //shows the defeat message when the user loses
    void showDefeat(QString);

    //clears the UI
    void blankUI();

    int getDegrees(MovableObject* obj);

    void disableWidgets();
};

#endif // INTERFACE_H
