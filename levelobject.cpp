#include "levelobject.h"
#include "levelmanager.h"
#include "interface.h"
#include "mainwindow.h"
#include <math.h>
#include <QMessageBox>

int LevelObject::nextId = 0;

//TODO: write this file
LevelObject::LevelObject(int initX, int initY, int initWidth, int initHeight, QObject *parent) :
    QObject(parent), id(++nextId), x(initX), y(initY), width(initWidth), height(initHeight),
    isMovable(false), isDestroyable(false), timer(new QTimer(this)) {
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->setInterval(20);
}

int LevelObject::getId() {
    return id;
}

QRect LevelObject::getGeometry() {
    QRect geometry(x,y,width,height);
    return geometry;
}

void LevelObject::destroy() {
    if (isDestroyable) {
        LevelManager::getInstance().destroy(this);
    }
}

void LevelObject::pause() {
    timer->stop();
}

void LevelObject::resume() {
    timer->start();
}

LevelObject::~LevelObject() {
    timer->stop();
    delete timer;
}

void LevelObject::onTimeOut() {}

MovableObject::MovableObject(int initX, int initY, int initWidth, int initHeight, QObject *parent):
    LevelObject(initX, initY, initWidth, initHeight, parent) {
    isMovable = true;
}

void MovableObject::move(int /*newX*/, int /*newY*/) {}

LevelObject* MovableObject::getContactedObject() {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        if (obj->getGeometry().intersects(this->getGeometry()) && obj->getId() != this->getId()) {
            return obj;
        }
    }
    return nullptr;
}

TankObject::TankObject(int x, int y, QObject *parent):
    MovableObject(x, y, 20, 20, parent), turretAngle(0) {
    isDestroyable = true;
}

void TankObject::move(int newX, int newY) {
    x = newX;
    y = newY;
}

void TankObject::startMotion(Direction dToMove) {
    d = dToMove;
    timer->start();
}

void TankObject::stopMotion() {
    timer->stop();
}

void TankObject::setTurret(int angle) {
    turretAngle = angle;
}

void TankObject::destroy() {
    //ending the game
    LevelManager::getInstance().setStopTimer(true);
    QString s = "Sorry, " + LevelManager::getUserName() + " lost";
    Interface::getInstance().showDefeat(s);
    //TODO: define this method
}

void TankObject::onTimeOut() {
    int amountToMove = 5;
    switch (d) {
    case North: y -= amountToMove; break;
    case South: y += amountToMove; break;
    case East:  x += amountToMove; break;
    case West:  x -= amountToMove; break;
    }
    if (getContactedObject() != nullptr) {
        // undo move
        switch (d) {
        case North: y += amountToMove; break;
        case South: y -= amountToMove; break;
        case East:  x -= amountToMove; break;
        case West:  x += amountToMove; break;
        }
    }
    LevelManager::getInstance().updateUI();
}

BulletObject::BulletObject(int initX, int initY, double initHeading, TankObject* initTank, QObject *parent):
    MovableObject(initX,initY, 20, 10, parent), heading(initHeading), tank(initTank) {
    isDestroyable = true;
}

void BulletObject::move(int newX, int newY) {
    x = newX;
    y = newY;
}

void BulletObject::startMotion() {
    timer->start();
}

void BulletObject::onTimeOut() {
    int amountToMove = 10;
    int moveX = cos(heading) * amountToMove;
    int moveY = sin(heading) * amountToMove;
    x += moveX;
    y += moveY;
    LevelObject* objectHit = getContactedObject();
    if (objectHit != nullptr && objectHit != tank) { // don't shoot myself
        this->destroy();
        objectHit->destroy();
    }
    LevelManager::getInstance().updateUI();
}

WallObject::WallObject(int x, int y, int width, int height, QObject *parent):
    LevelObject(x, y, width, height, parent) {}

Barricade::Barricade(int x, int y, QObject *parent):
    LevelObject(x, y, 20, 20, parent) {
    isDestroyable = true;
}

void Barricade::destroy() {
    //TODO: write this method
}

Target::Target(int initX, int initY, QObject *parent):
    TankObject(initX, initY, parent){}

void Target::destroy() {
    LevelManager::getInstance().setStopTimer(true);
    QString s = "Enemy Tank destroyed";
    Interface::getInstance().showVictory();
    //code for winning game
}
