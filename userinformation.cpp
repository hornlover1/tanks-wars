//--------------------------------------------------------------
// File:   userinformation.cpp
// Author: Jordan Fleck  Team: Barnabas  Class: CpS 111
// Desc: This file contains all the information needed to store
//      user save information, as well as highscore, highest
//      level reached, and what level the user is currently on.
//--------------------------------------------------------------

#include "userinformation.h"
#include "levelmanager.h"

UserInformation::UserInformation(QObject *parent): QObject(parent) {
    userTime = "Easy";
}

UserInformation UserInformation::instance;

UserInformation& UserInformation::getInstance() {
    return instance;
}

QString UserInformation::getUserTime() {
    return userTime;
}

void UserInformation::selectTime(QString s) {
    userTime = s;
}

void UserInformation::setLevelNumber(int levelNum) {
    currentLevelNumber = levelNum;
}

int UserInformation::getLevel() {return currentLevelNumber;}

int UserInformation::lastUnlockedLevel = 1;

int UserInformation::getUserHighScore() {
    return userHighScore;
}

void UserInformation::setHighScore() {
    if(userTime == "Easy") {
        userHighScore = 10 * LevelManager::getInstance().getEasyTime();
    } else if(userTime == "Medium") {
        userHighScore = 15 * LevelManager::getInstance().getMediumTime();
    } else if (userTime == "Hard") {
        userHighScore = 20 * LevelManager::getInstance().getHardTime();
    }
}

QString UserInformation::getUserName() {
    return userName;
}

void UserInformation::setUserName(QString name) {
       userName = name;
}

void UserInformation::incrementLastUnlockedLevel() {
    if (lastUnlockedLevel < 9) {
        lastUnlockedLevel++;
    }
}

void UserInformation::setLastUnlockedLevel(int i) {
  lastUnlockedLevel = i;
}

int UserInformation::getLastUnlockedLevel() {
    return lastUnlockedLevel;
}
