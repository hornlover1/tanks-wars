#include "opponentmanager.h"

OpponentManager::OpponentManager() {}

OpponentManager OpponentManager::instance;

OpponentManager OpponentManager::getInstance() {
    return instance;
}

void OpponentManager::startTankMoving(Direction d) {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            targ->startMotion(d);
        }
    }
}

void OpponentManager::stopTankMoving() {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        Target* targ = dynamic_cast<Target*>(obj);
        if (targ != nullptr) {
            targ->stopMotion();
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
