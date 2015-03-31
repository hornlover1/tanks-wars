#include "levelobject.h"
#include "levelmanager.h"
#include "interface.h"
#include "mainwindow.h"
#include <math.h>
#include <QMessageBox>
#include <QtMultimedia/QMediaPlayer>
#include <QFileInfo>

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

QString LevelObject::getImagePath()
{
    return imagePath;
}

QRect LevelObject::getGeometry() {
    QRect geometry(x,y,width,height);
    return geometry;
}

void LevelObject::destroy() {
    if (isDestroyable) {
        LevelManager::getInstance().destroy(this);
        LevelManager::getInstance().setBullet_obj(false);
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

QRect MovableObject::getGeometry() {
    if(directionFaced == West || directionFaced == East) {
        QRect geometry(x,y,height,width);
        return geometry;
    }
    else {
        QRect geometry(x,y,width,height);
        return geometry;
    }
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

void MovableObject::setDirectionFaced(Direction direction) {
    directionFaced = direction;
}

void MovableObject::setD(Direction direction) {
    d = direction;
}

Direction MovableObject::getD() {
    return d;
}

Direction MovableObject::getDirectionFaced(){
    return directionFaced;
}

TankObject::TankObject(int x, int y, QObject *parent):
    MovableObject(x, y, 20, 50, parent), turretAngle(0) {
    isDestroyable = true;
    //load the picture
    imagePath = ":/images/Resources/Tank1.png";
    directionFaced = North;
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
    QString s = "Mission Failed: You have lost " + LevelManager::getUserName() + ".";
    Interface::getInstance().showDefeat(s);

    //TODO: define this method - possibly to show awsome graphics
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
    imagePath = ":/images/Resources/Bullet.png";
    directionFaced = East;
}

void BulletObject::move(int newX, int newY) {
    x = newX;
    y = newY;
}

void BulletObject::startMotion() {
    timer->start();
}

void BulletObject::onTimeOut() {
    bool play = false;
    double amountToMove = 10.0;
    double moveX = cos(heading) * amountToMove;
    double moveY = sin(heading) * amountToMove;
    x += moveX;
    y += moveY;
    qDebug() << "moveX: " << moveX;
    qDebug() << "moveY: " << moveY;
    qDebug() << "x: " << x;
    qDebug() << "y: " << y;
    LevelObject* objectHit = getContactedObject();
    if (objectHit != nullptr && objectHit != tank) { // don't shoot myself
        this->destroy();
        objectHit->destroy();
        play = true;
    }
    if(play == true){
        /*
        QMediaPlayer player;
        player.setMedia(QUrl::fromLocalFile(QFileInfo(":/sounds/Resources/boom4.mp3").absoluteFilePath()));
        player.setVolume(100);
        player.setMuted(false);
        player.play();
        */
        LevelManager::getInstance().updateUI();
    }
    else{
        LevelManager::getInstance().updateUI();
    }
}

WallObject::WallObject(int x, int y, int width, int height, QObject *parent):
    LevelObject(x, y, width, height, parent)
{
    imagePath = ":/images/Resources/Wall.jpg";
}

Barricade::Barricade(int x, int y, QObject *parent):
    LevelObject(x, y, 20, 20, parent) {
    isDestroyable = true;
    imagePath = ":/images/Resources/Barracade.png";
}

Target::Target(int initX, int initY, QObject *parent):
    TankObject(initX, initY, parent){isDestroyable = true;}

void Target::destroy() {
    LevelManager::getInstance().setStopTimer(true);
    Interface::getInstance().showVictory();
    //code for winning game
}
