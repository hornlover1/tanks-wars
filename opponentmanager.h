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
    void setTurret(double& num);
    void fireBullet(int x, int y, double heading);
    void setTurret(double angle);
};

#endif // OPPONENTMANAGER_H
