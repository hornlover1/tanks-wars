//--------------------------------------------------------------
// File:   levelmanager.cpp
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains the code to edit the level. It
//      contains clocks, the vector of objects, and the level
//      information.
//--------------------------------------------------------------

#include "levelmanager.h"
#include "interface.h"
#include <QFile>
#include <QTextStream>
#include <math.h>
#include <iostream>
#include <QDebug>
#include "networkmanager.h"
#include "userinformation.h"
#include "userinformation.h"
using namespace std;

LevelManager LevelManager::instance;

int LevelManager::getEasyTime() {return easyTime;}
int LevelManager::getMediumTime() {return mediumTime;}
int LevelManager::getHardTime() {return hardTime;}

//called by a QTimer to decremented the user's selected time
void LevelManager::decrementTime() {
    if (easyTime <= 0 || mediumTime <= 0 || hardTime <= 0) {
        return;
    }
    if (UserInformation::getInstance().getUserTime() == "Easy") {
        easyTime--;
        Interface::getInstance().showTime(QString::number(easyTime));
    } else if(UserInformation::getInstance().getUserTime() == "Medium") {
        mediumTime--;
        Interface::getInstance().showTime(QString::number(mediumTime));
    } else if (UserInformation::getInstance().getUserTime() == "Hard") {
        hardTime--;
        Interface::getInstance().showTime(QString::number(hardTime));
    }

    if (easyTime == 0 || mediumTime == 0 || hardTime == 0) {
        LevelManager::setStopTimer(true);
        Interface::getInstance().showDefeat("Sorry, time up.");
    }
}

LevelManager& LevelManager::getInstance() {
    return instance;
}

vector<LevelObject*> LevelManager::getObjects() {
    return objectsInLevel;
}

void LevelManager::setStopTimer(bool b) {
    stopTimer = b;
}

//this slot will call two methods to manipulate the Target object
void LevelManager::AI() {
    //fire on the user's tank
    //Issue command to fire
    bool loadedTank = false;
    TankObject* tank = nullptr;
    Target* target = nullptr;
    for (LevelObject* obj: objectsInLevel) {
        if (obj->getIsMovable() == true) {
            if (loadedTank == false) {
                tank = dynamic_cast<TankObject*>(obj);
                loadedTank = true;
            } else {
                target = dynamic_cast<Target*>(obj);
            }
        }
        if (tank != nullptr && target != nullptr) {
            //may be able to use these values to calculate the bullet's direction.
            double diffX = tank->getX() - target->getX();
            double diffY = tank->getY() - target->getY();
            double slope = diffY/diffX;
            double heading = atan(slope);
            double pi = 3.14159265358979323846264338327950288419716;
            if (diffX <= 0) {
                heading += pi; // add pi to rotate it 180 degrees so that it shoots in the right direction
            }
            fireBullet(target->getX(), target->getY(), heading, target);
            break;
        }
    }
}

bool LevelManager::getStopTimer() {return stopTimer;}

void LevelManager::loadLevel(int levelNum, bool isPrimary) {
    for (LevelObject* obj: objectsInLevel) {
        Interface::getInstance().deleteObject(obj);
        delete obj;
    }
    //start the timer back up again so that the countdown works
    stopTimer = false;

    objectsInLevel.clear();

    UserInformation::getInstance().setLevelNumber(levelNum); //I need this number for saveHighScore()

    //i.e. level2.txt
    //QFile levelX("://Resources/level1.txt");
    QFile levelX("://Resources/level" + QString::number(levelNum) + ".txt");
    levelX.open(QIODevice::ReadOnly);
    QTextStream strm(&levelX);

    QString argType;
    while (!(strm >> argType).atEnd()) {
        if (argType == "time") {
            strm >> easyTime >> mediumTime >> hardTime;
        } else if (argType == "wall") {
            int x, y, width, height;
            strm >> x >> y >> width >> height;

            qDebug() << "x" << x << "y" << y << "w" << width << "h" << height;

            LevelObject* obj = new WallObject(x, y, width, height);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if ((argType == "tank" && isPrimary) || (argType == "tank2" && !isPrimary)) {
            int x, y;
            strm >> x >> y;

            qDebug() << "x" << x << "y" << y;

            LevelObject* obj = new TankObject(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if ((argType == "tank2" && isPrimary) || (argType == "tank" && !isPrimary)) {
            int x, y;
            strm >> x >> y;

            qDebug() << "x" << x << "y" << y;

            LevelObject* obj = new Target(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if (argType == "barricade") {
            int x, y;
            strm >> x >> y;

            qDebug() << "x" << x << "y" << y;

            LevelObject* obj = new Barricade(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        }
    }
}

//loop through all objects. If movable, then call moveObject() to update position
void LevelManager::updateUI() {
    for (LevelObject* obj: objectsInLevel) {
        MovableObject* mv;
        if (obj->getIsMovable() == true) {
            mv = dynamic_cast<MovableObject*>(obj);
            if (mv == nullptr) {
                continue;
            }
        } else {
            continue;
        }
        Interface::getInstance().moveObject(mv);
    }
}

void LevelManager::moveMouse(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void LevelManager::mouseClick() {
    if(stopTimer == false) {
        TankObject* tank;
        Target* target;
        for (LevelObject* obj: objectsInLevel) {
            if (obj->getIsMovable() == true) {
                tank = dynamic_cast<TankObject*>(obj);
                target = dynamic_cast<Target*>(obj);
            }
            if (tank == nullptr || target != nullptr) {
                continue;
            }
            //may be able to use these values to calculate the bullet's direction.
            double diffX = mouseX - tank->getX();
            double diffY = mouseY - tank->getY();
            double slope = diffY/diffX;
            double heading = atan(slope);
            double pi = 3.14159265358979323846264338327950288419716;
            if (diffX <= 0) {
                heading += pi; // add pi to rotate it 180 degrees so that it shoots in the right direction
            }
            fireBullet(tank->getX(), tank->getY(), heading, tank);
            NetworkManager::getInstance().bullet(tank->getX(), tank->getY(), heading);
            break;
        }
    }
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
    //get tank
    //start tank moving
    //update interface when tank moves - how to do?
    TankObject* tank;
    for (LevelObject* obj: objectsInLevel) {
        tank = dynamic_cast<TankObject*>(obj);
        Target* target = dynamic_cast<Target*>(obj);
        if (tank == nullptr || target != nullptr) {
            //We're looking for the tank, not the tank2
            continue;
        } else {
            break;
        }
    }
    tank->startMotion(d);
    NetworkManager::getInstance().startTank(tank->getX(), tank->getY(), d);
}

void LevelManager::keyRelease(Direction /*d*/) {
    //get tank
    //stop tank moving
    TankObject* tank;
    for (LevelObject* obj: objectsInLevel) {
        tank = dynamic_cast<TankObject*>(obj);
        Target* target = dynamic_cast<Target*>(obj);
        if (tank == nullptr || target != nullptr) {
            continue;
        } else {
            break;
        }
    }
    tank->stopMotion();
    NetworkManager::getInstance().stopTank(tank->getX(), tank->getY());
}

//deletes the object from the list of objectsInLevel
void LevelManager::destroy(LevelObject *obj) {
    for (auto i = objectsInLevel.begin(); i < objectsInLevel.end(); i++) {
        if ((*i)->getId() == obj->getId()) {
            Interface::getInstance().deleteObject(obj); //hide label and delete later
            delete (*i); //delete the object itself
            objectsInLevel.erase(i); //erase object from list of game objects
        }
    }
}

LevelManager::~LevelManager() {

}

void LevelManager::fireBullet(int x, int y, double heading, TankObject* tank) {
    BulletObject* Bobj = new BulletObject(x, y, heading, tank);
    objectsInLevel.push_back(Bobj);
    Interface::getInstance().drawObject(Bobj);
    Bobj->startMotion();
}

void LevelManager::deleteAllObjects() {
    for (LevelObject* obj: objectsInLevel) {
        delete obj;
    }
    objectsInLevel.clear();
}
