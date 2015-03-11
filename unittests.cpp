#include "levelmanager.h"
#include "unittests.h"
#include <vector>
#include "levelobject.h"
#include <cassert>

void runUnitTests() {
    LevelManager::getInstance().loadLevel(1);
    checkLevelOne();
    checkMovingTank();
    checkFiringBullet();
}

/*
Level 1 should look like:
time 30 25 20
wall 0 0 200 200
wall 0 400 200 200
tank 50 300
wall 380 100 40 400
wall 600 0 200 200
tank2 550 200
wall 600 400 200 200
wall 0 -50 800 50
wall -50 0 50 600
wall 0 600 800 50
wall 800 0 50 600
*/

void checkLevelOne() {
    vector<LevelObject*> objects = LevelManager::getInstance().getObjects();
    assert(objects.size() == 12);
    //need getters
//    assert(LevelManager::getInstance().getEasyTime() == 30);
//    assert(LevelManager::getInstance().getMediumTime() == 25);
//    assert(LevelManager::getInstance().getHardTime() == 20);
}

void checkMovingTank() {

}

void checkFiringBullet() {

}
