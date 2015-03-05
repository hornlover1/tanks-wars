#ifndef INTERFACE_H
#define INTERFACE_H

class Interface {
    Interface();
    static Interface instance;
public:
    //singleton class
    Interface getInstance();

    //draw the object on the screen
    void drawObject(LevelObject* obj);

    //move the object around on the screen
    void moveObject(LevelObject* obj);

    //take the object representing the LevelObject off the screen
    void deleteObject(LevelObject* obj);
};

#endif // INTERFACE_H
