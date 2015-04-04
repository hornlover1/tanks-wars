//--------------------------------------------------------------
// File:   opponentmanager.h
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains the info for the other player in
//      multiplayer, allowing the program to compute 2 tanks
//      moving and shooting.
//--------------------------------------------------------------

#ifndef OPPONENTMANAGER_H
#define OPPONENTMANAGER_H

#include "levelmanager.h"

class OpponentManager {
    OpponentManager();
    static OpponentManager instance;
public:
    static OpponentManager getInstance();
    void startTankMoving(int x, int y, Direction d);
    void stopTankMoving(int x, int y);
    void setTurret(double& num);
    void fireBullet(int x, int y, double heading);
    void setTurret(double angle);
};

#endif // OPPONENTMANAGER_H
