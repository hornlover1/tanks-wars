#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "levelobject.h"
#include <fstream>
#include <sstream>
#include <QTimer>
using namespace std;

class LevelManager {
    LevelManager();
    static LevelManager instance;
    //objects that exist in the level and should be shown on the screen
    vector<LevelObject*> objectsInLevel;
    //number of seconds given for a particular difficulty level
    int easyTime, mediumTime, hardTime;

    //position of mouse
    int mouseX, mouseY;
/*
//User Information
    //counter to record which level is available
    static int lastUnlockedLevel;

    //The name of the user
    static QString userName;

    //current high score of the user
    int userHighScore;
*/
public:
    /*
    //set userHighScore
    void setUserHighScore(int score);

    //returns userHighScore
    int getUserHighScore();

    //get the username
    static QString getUserName();

    //set the username
    static void setUserName(string name);

    //increment levelUnlockedLevel
    static void incrementLastUnlockedLevel();

    //code used by the load method to set the variable.
    static void setLastUnlockedLevel(int i);

    static int getLastUnlockedLevel();
    //TODO: need to write the code incrementing this after each level completion
*/
    //singleton method
    static LevelManager& getInstance();

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

    //save game to a file
    void saveFile();

    //save highscore to a file
    void saveHighScore();

    //read in the saved file
    bool loadFile();

    void updateUI();

    ~LevelManager();
};

#endif // LEVELMANAGER_H
