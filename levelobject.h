#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <QObject>

class LevelObject : public QObject {
    Q_OBJECT

protected :
    virtual bool isDestroyable;

    virtual bool isMovable;

    int x, y, height, width;
    //timer to be used to animate movableObjects
    QTimer timer;
public:
    explicit LevelObject(QObject* parent = 0);

    //getters and setters

    //get a rectangle representing the object for calculations especially involving overlapping of objects
    QRect getGeometry();

    //for objects that are destroyable, blow them up, preferably with cool animation
    virtual void destroy();

    //pause the timer to stop animation
    void pause();

    //resume the timer to restart animation
    void resume();
};

//an object that can move around on the screen, such as a tank or bullet
class MovableObject: public LevelObject {
    //isMovable = true;
public:
    MovableObject(QObject* parent = 0);

    //moves the object to the new location
    virtual void move(int newX, int newY);

    //if the object overlaps with another object, get the object it is in contact with, otherwise return nullptr
    LevelObject * getContactedObject();
};

enum Direction {North, South, East, West};

class TankObject: public MovableObject {
    //isDestroyable=true
    //the angle, in degrees, that the turret is facing
    int turretAngle;
public:
    TankObject(QObject* parent = 0);

    //move the tank to the new location
    void move(int newX, int newY);

    //when the user holds down a particular arrow key, start the tank moving
    void startMotion(Direction d);

    //aim the turret in that direction
    void setTurret(int angle);

    //blow up the tank, preferably with cool animation
    void destroy();
public slots:
    //move 5px in the direction specified
    void move(Direction d);
};

class BulletObject: public MovableObject  {
    //isDestroyable=false
    //the angle, in degrees, that the bullet is moving
    int heading;
public:
    BulletObject(int heading, QObject* parent = 0);

    //move the bullet
    void move(int newX, int newY);

    //set the timer to start the bullet moving
    void startMotion();

public slots:
    //move the bullet 5px in the direction specified by <heading>
    void move();
};

class WallObject: public LevelObject {
    //isMovable=false
    //isDestroyable=false
public:
    WallObject(QObject* parent = 0);
};

class Barricade: public LevelObject {
    //isMovable=false
    //isDestroyable=true

public:
    Barricade(QObject* parent = 0);

    //get rid of the barricade
    void destroy();
};

#endif // LEVELOBJECT_H
