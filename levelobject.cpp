#include "levelobject.h"

int LevelObject::nextId = 0;

//TODO: write this file
LevelObject::LevelObject(int initX, int initY, int initWidth, int initHeight, QObject *parent) :
    QObject(parent), id(++nextId), x(initX), y(initY), width(initWidth), height(initHeight),
    isMovable(false), isDestroyable(false), timer(new QTimer(this)) {
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
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

LevelObject::onTimeOut() {}
