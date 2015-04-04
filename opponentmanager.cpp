//--------------------------------------------------------------
// File:   opponentmanager.cpp
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains the info for the other player in
//      multiplayer, allowing the program to compute 2 tanks
//      moving and shooting.
//--------------------------------------------------------------

#include "opponentmanager.h"

OpponentManager::OpponentManager() {}

OpponentManager OpponentManager::instance;

OpponentManager OpponentManager::getInstance() {
    return instance;
}

void OpponentManager::startTankMoving(int x, int y, Direction d) {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            targ->move(x, y);
            targ->startMotion(d);
        }
    }
}

void OpponentManager::stopTankMoving(int x, int y) {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            targ->stopMotion();
            targ->move(x, y);
        }
    }
}

void OpponentManager::fireBullet(int x, int y, double heading) {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            LevelManager::getInstance().fireBullet(x, y, heading, targ);
        }
    }
}

void OpponentManager::setTurret(double angle) {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            targ->setTurret(angle);
        }
    }
}
