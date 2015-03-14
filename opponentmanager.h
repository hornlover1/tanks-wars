#ifndef OPPONENTMANAGER_H
#define OPPONENTMANAGER_H

#include "levelmanager.h"

class OpponentManager {
    OpponentManager();
    static OpponentManager instance;
public:
    static OpponentManager getInstance();
    void startTankMoving(Direction d);
    void stopTankMoving();
    void fireBullet(int x, int y, int heading);
};

#endif // OPPONENTMANAGER_H
