#include "levelobject.h"
#include "levelmanager.h"
#include <math.h>

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

void LevelObject::destroy() {}

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

void MovableObject::move(int newX, int newY) {}

LevelObject* MovableObject::getContactedObject() {
    for (LevelObject* obj: LevelManager::getInstance().getObjects()) {
        if (obj->getGeometry().contains(this->getGeometry())) {
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

void TankObject::startMotion(Direction d) {
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(move(d)));
}

void TankObject::stopMotion() {
    timer->stop();
}

void TankObject::setTurret(int angle) {
    turretAngle = angle;
}

void TankObject::destroy() {
    //TODO: define this method
}

void TankObject::move(Direction d) {
    int amountToMove = 5;
    switch (d) {
    case North: y -= amountToMove; break;
    case South: y += amountToMove; break;
    case East:  x += amountToMove; break;
    case West:  x -= amountToMove; break;
    }
}

BulletObject::BulletObject(int initX, int initY, int initHeading, QObject *parent):
    MovableObject(initX,initY, 20, 10, parent), heading(initHeading) {}

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
