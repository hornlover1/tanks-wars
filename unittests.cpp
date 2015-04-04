//--------------------------------------------------------------
// File:   unittests.cpp
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file's only purpose is to run the unit test. This
//      file in particular contains the various debug statements
//      for the test.
//--------------------------------------------------------------

#include <cassert>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <vector>

#include "levelobject.h"
#include "levelmanager.h"
#include "unittests.h"

/*
Level 0 should look like:
time 1000 100 15
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
barricade 240 310
barricade 240 325
barricade 240 350
*/

void checkLevelZero() {
    vector<LevelObject*> objects = LevelManager::getInstance().getObjects();
    qDebug() << objects.size();
    assert(objects.size() == 14); //time doesn't count

    assert(LevelManager::getInstance().getEasyTime() == 1000);
    assert(LevelManager::getInstance().getMediumTime() == 100);
    assert(LevelManager::getInstance().getHardTime() == 15);

    qDebug() << "The difficulty times were sucessfully loaded from the file.";

    WallObject* wall = dynamic_cast<WallObject*>(objects.at(0));
        assert(wall->getX() == 0);
        assert(wall->getY() == 0);

        qDebug() << "Object 0";

    wall = dynamic_cast<WallObject*>(objects.at(1));
        assert(wall->getX() == 0);
        assert(wall->getY() == 400);

        qDebug() << "obj 1";

    TankObject* tank = dynamic_cast<TankObject*>(objects.at(2));
        assert(tank->getX() == 50);
        assert(tank->getY() == 300);

        qDebug() << "obj 2";

    wall = dynamic_cast<WallObject*>(objects.at(3));
        assert(wall->getX() == 380);
        assert(wall->getY() == 100);

        qDebug() << "obj 3";

    wall = dynamic_cast<WallObject*>(objects.at(4));
        assert(wall->getX() == 600);
        assert(wall->getY() == 0);

        qDebug() << "obj 4";

        // tests for tank2 go here
    Target* target = dynamic_cast<Target*>(objects.at(5));
        assert(target->getX() == 550);
        assert(target->getY() == 200);

        qDebug() << "obj 5";

    wall = dynamic_cast<WallObject*>(objects.at(6));
        assert(wall->getX() == 600);
        assert(wall->getY() == 400);

        qDebug() << "obj 6";

    wall = dynamic_cast<WallObject*>(objects.at(7));
        assert(wall->getX() == 0);
        assert(wall->getY() == -50);

         qDebug() << "obj 7";

    wall = dynamic_cast<WallObject*>(objects.at(8));
        assert(wall->getX() == -50);
        assert(wall->getY() == 0);

         qDebug() << "obj 8";

    wall = dynamic_cast<WallObject*>(objects.at(9));
        assert(wall->getX() == 0);
        assert(wall->getY() == 600);

         qDebug() << "obj 9";

    wall = dynamic_cast<WallObject*>(objects.at(10));
        assert(wall->getX() == 800);
        assert(wall->getY() == 0);

        qDebug() << "obj 10";

    Barricade* barricade = dynamic_cast<Barricade*>(objects.at(11));
        assert(barricade->getX() == 240);
        assert(barricade->getY() == 310);

        qDebug() << "obj 11";

    barricade = dynamic_cast<Barricade*>(objects.at(12));
        assert(barricade->getX() == 240);
        assert(barricade->getY() == 325);

        qDebug() << "obj 12";

    barricade = dynamic_cast<Barricade*>(objects.at(13));
        assert(barricade->getX() == 240);
        assert(barricade->getY() == 350);

        qDebug() << "obj 13";

        qDebug() << "Objects loaded and ready for use.";
}

void checkMovingTank() {
    /*LevelManager::getInstance().keyPress(South); // should be able to move 80px south, which should take 320ms
    QThread::msleep(500);
    LevelManager::getInstance().keyRelease(South);
    qDebug() << LevelManager::getInstance().getObjects()[2]->getY();
    assert(LevelManager::getInstance().getObjects()[2]->getY() == 380);
    */assert(LevelManager::getInstance().getObjects()[2]->getX() == 50);
}

void checkFiringBullet() {
    /*LevelManager::getInstance().moveMouse(0, 380); //should fire straight to the left and should take 200ms to get there
    QThread::msleep(110);
    assert(LevelManager::getInstance().getObjects()[11]->getX() == 25);
    assert(LevelManager::getInstance().getObjects()[11]->getY() == 380);
    QThread::msleep(200); //bullet should be destroyed by now
    assert(LevelManager::getInstance().getObjects().size() == 11);*/
}

void runUnitTests() {
    LevelManager::getInstance().loadLevel(0);
    checkLevelZero();
    checkMovingTank();
    checkFiringBullet();
}
