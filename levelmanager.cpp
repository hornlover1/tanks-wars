#include "levelmanager.h"

LevelManager::LevelManager() {}

LevelManager LevelManager::instance;

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
