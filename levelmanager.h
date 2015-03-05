#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "levelobject.h"

class LevelManager {
    LevelManager();
    static LevelManager instance;
    //objects that exist in the level and should be shown on the screen
    vector<LevelObject*> objectsInLevel;
    //number of seconds given for a particular difficulty level
    int easyTime, mediumTime, hardTime;

    //position of mouse
    int mouseX, mouseY;

public:
    //singleton method
    LevelManager getInstance();

    //get all objects in the level
    vector<LevelObject*> getObjects();

    //delete everything currently stored in level and load a new level from a file.
    //the level files will be in the root of the project directory with the names level1.txt, level2.txt...
    void loadLevel(int levelNum);

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
};

#endif // LEVELMANAGER_H
