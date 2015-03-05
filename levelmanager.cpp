#include "levelmanager.h"

LevelManager::LevelManager() {}

LevelManager LevelManager::instance;

void LevelManager::setUserHighScore(int score)
{
    userHighScore = score;
}

int LevelManager::getUserHighScore()
{
    return userHighScore;
}

int LevelManager::lastUnlockedLevel;

QString LevelManager::getUserName()
{
    return userName;
}

void LevelManager::setUserName(QString name)
{
       userName = name;
}

void LevelManager::incrementLastUnlockedLevel(){
    if(lastUnlockedLevel < 9){
        lastUnlockedLevel++;
    }
}

int LevelManager::getLastUnlockedLevel(){
    return lastUnlockedLevel;
}

LevelManager LevelManager::getInstance() {
    return instance;
}

void LevelManager::loadLevel(int levelNum) {
    for (LevelObject* obj: objectsInLevel) {
        delete obj;
    }
    objectsInLevel.clear();
    //TODO: load the next level from file
}

void LevelManager::moveMouse(int x, int y) {
    mouseX = x;
    mouseY = y;
    //TODO: write logic to move the turret
}

void LevelManager::mouseClick() {
    //TODO: fire a bullet at the target
}

void LevelManager::pause() {
    for (LevelObject* obj: objectsInLevel) {
        obj->pause();
    }
}

void LevelManager::resume() {
    for (LevelObject* obj: objectsInLevel) {
        obj->resume();
    }
}

void LevelManager::keyPress(Direction d) {
    //TODO: write this method
    //get tank
    //start tank moving
    //update interface when tank moves - how to do?
}

void LevelManager::keyRelease(Direction d) {
    //TODO: write this method
    //get tank
    //stop tank moving
}

void LevelManager::saveFile()
{
    //open\create the file
    ofstream fs("saveFile.txt");

    //write last unlocked level
    fs << "maxLevel \"" << LevelManager::getLastUnlockedLevel() << "\"";

    //write user name
    fs << "user.name \"" << getUserName() << "\"";

    //close file
    fs.close();
}

void LevelManager::saveHighScore()
{
    ofstream os("HighScore.txt");

    //write out name
    os << getUserName() << ":" << endl << endl;

    //write out highscore
    os << getUserHighScore();

    //close file
    os.close();
}

void LevelManager::loadFile()
{

}
