//--------------------------------------------------------------
// File:   levelmanager.h
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains the code to edit the level. It
//      contains clocks, the vector of objects, and the level
//      information.
//--------------------------------------------------------------

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "levelobject.h"
#include <QTimer>
using namespace std;

class LevelManager {
    //LevelManager();
    static LevelManager instance;
    //objects that exist in the level and should be shown on the screen
    vector<LevelObject*> objectsInLevel;

    //number of seconds given for a particular difficulty level
    int easyTime, mediumTime, hardTime;

    //position of mouse
    int mouseX, mouseY;

    //boolean to hold whether game timer should be stopped
    bool stopTimer;

public:
    //singleton method
    static LevelManager& getInstance();

    //attempts at a basic AI in case it is required
    void AI();

    //get all objects in the level
    vector<LevelObject*> getObjects();

    //delete everything currently stored in level and load a new level from a file.
    //the level files will be in the root of the project directory with the names level1.txt, level2.txt...
    void loadLevel(int levelNum, bool isPrimary = true);

    //on a mousemove, this will reposition the tank's turret
    void moveMouse(int x, int y);

    //start a bullet moving
    void mouseClick();

    //pause all timers in play
    void pause();

    //resume all the timers
    void resume();

    //start the tank moving in a particular direction
    void keyPress(Direction d);

    //stop the tank from moving
    void keyRelease(Direction d);

    void updateUI();

    void destroy(LevelObject* obj);

    void fireBullet(int x, int y, double heading, TankObject* tank);

    //to access times
    int getEasyTime();
    int getMediumTime();
    int getHardTime();

    //called by a QTimer to decremented the user's selected time
    void decrementTime();

    //bool to manipulate the time flag that manipulates the entire gameplay
    void setStopTimer(bool);
    bool getStopTimer();

    static int getLastUnlockedLevel();

    void deleteAllObjects();

    ~LevelManager();
};

#endif // LEVELMANAGER_H
