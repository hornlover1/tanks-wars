#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <QObject>

class LevelObject : public QObject {
    Q_OBJECT
public:
    explicit LevelObject(QObject *parent = 0);

    virtual bool isDestroyable;

    virtual bool isMovable;

    int x, y, height, width;

    //getters and setters

    //get a rectangle representing the object for calculations especially involving overlapping of objects
    QRect getGeometry();

};

#endif // LEVELOBJECT_H
