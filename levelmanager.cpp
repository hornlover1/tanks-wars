#include "levelmanager.h"
#include "interface.h"
#include <QFile>
#include <QTextStream>
#include <math.h>
#include <cassert>
#include <iostream>
using namespace std;

QString LevelManager::userName = "";

int LevelManager::lastUnlockedLevel = 1;

LevelManager::LevelManager() {}

LevelManager LevelManager::instance;

int LevelManager::getEasyTime() {return easyTime;}
int LevelManager::getMediumTime() {return mediumTime;}
int LevelManager::getHardTime() {return hardTime;}


void LevelManager::setUserHighScore(int score) {
    userHighScore = score;
}

int LevelManager::getUserHighScore() {
    return userHighScore;
}


QString LevelManager::getUserName() {
    return LevelManager::userName;
}

void LevelManager::setUserName(QString name) {
       LevelManager::userName = name;
}

void LevelManager::incrementLastUnlockedLevel() {
    if(lastUnlockedLevel < 9){
        lastUnlockedLevel++;
    }
}

void LevelManager::setLastUnlockedLevel(int i) {
  lastUnlockedLevel = i;
}

int LevelManager::getLastUnlockedLevel() {
    return lastUnlockedLevel;
}

LevelManager& LevelManager::getInstance() {
    return instance;
}

vector<LevelObject*> LevelManager::getObjects() {
    return objectsInLevel;
}

void LevelManager::loadLevel(int levelNum) {
    for (LevelObject* obj: objectsInLevel) {
        Interface::getInstance().deleteObject(obj);
        delete obj;
    }
    objectsInLevel.clear();

    //i.e. level2.txt
    //QFile levelX("://Resources/level1.txt");
    QFile levelX("://Resources/level" + QString::number(levelNum) + ".txt");
    levelX.open(QIODevice::ReadOnly);
    QTextStream strm(&levelX);

    QString argType;
    while (!(strm >> argType).atEnd()) {
        if (argType == "time") {
            strm >> easyTime >> mediumTime >> hardTime;
        } else if (argType == "wall") {
            int x, y, width, height;
            strm >> x >> y >> width >> height;

            cout << "x" << x << "y" << y << "w" << width << "h" << height;

            LevelObject* obj = new WallObject(x, y, width, height);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if (argType == "tank") {
            int x, y;
            strm >> x >> y;

            cout << "x" << x << "y" << y;

            LevelObject* obj = new TankObject(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        }
    }
    //TODO: load the next level from file
}

void LevelManager::updateUI() {
    for (LevelObject* obj: objectsInLevel) {
        MovableObject* mv = dynamic_cast<MovableObject*>(obj);
        if (mv == nullptr) {
            continue;
        }
        Interface::getInstance().moveObject(mv);
    }
}

void LevelManager::moveMouse(int x, int y) {
    mouseX = x;
    mouseY = y;
    //TODO: write logic to move the turret
}

//Jordan manipulated obj
void LevelManager::mouseClick() {
    //TODO: fire a bullet at the target
    for (LevelObject* obj: objectsInLevel) {
        TankObject* tank = dynamic_cast<TankObject*>(obj);
        if (tank == nullptr) {
            continue;
        }
        double diffX = mouseX - tank->getX();
        double diffY = mouseY - tank->getY();
        double heading = atan(diffY/diffX);
        double pi = 3.14159265358979323846264338327950288;
        if (diffX <= 0) {
            heading += pi; // add pi to rotate it 180 degrees so that it shoots in the right direction
        }
        BulletObject* Bobj = new BulletObject(tank->getX(), tank->getY(), heading, tank);
        objectsInLevel.push_back(Bobj);
        Interface::getInstance().drawObject(Bobj);
        Bobj->startMotion();
    }
}

void LevelManager::pause() {
    for (LevelObject* obj: objectsInLevel) {
        obj->pause();
    }
}

void LevelManager::resume() {
    for (LevelObject* obj: objectsInLevel) {
        obj->resume();
    }
}

void LevelManager::keyPress(Direction d) {
    //TODO: write this method
    //get tank
    //start tank moving
    //update interface when tank moves - how to do?
    for (LevelObject* obj: objectsInLevel) {
        TankObject* tank = dynamic_cast<TankObject*>(obj);
        if (tank == nullptr) {
            continue;
        }
        tank->startMotion(d);
    }
}

void LevelManager::keyRelease(Direction /*d*/) {
    //TODO: write this method
    //get tank
    //stop tank moving
    for (LevelObject* obj: objectsInLevel) {
        TankObject* tank = dynamic_cast<TankObject*>(obj);
        if (tank == nullptr) {
            continue;
        }
        tank->stopMotion();
    }
}

void LevelManager::destroy(LevelObject *obj) {
    for (auto i = objectsInLevel.begin(); i <= objectsInLevel.end(); i++) {
        if ((*i)->getId() == obj->getId()) {
            Interface::getInstance().deleteObject(obj);
            objectsInLevel.erase(i);
            delete (*i);
        }
    }
}

LevelManager::~LevelManager() {

}

//writes userName and lastUnlockedLevel to a file. Accounts for previous saves.
void LevelManager::saveFile() {
    //c_string to read bytes into
    char c[20];

    //open the current saveFile
    ifstream in("saveFile.txt");

    //create a new file to write data into
    ofstream out("tempFile.txt");

    //loop through every line in file
    while(in.peek() != EOF)
    {
        //read data and put into a QString for comparison
        in.getline(c,20);
        QString info = QString(c);

        //if line not the userName
        if(info != LevelManager::getUserName())
        {
            //write this line and the next one
            out << c << endl;

            in.getline(c,20);

            out << c << endl;
        }
        //if line is userName, then do not write this line
        if(info == LevelManager::getUserName())
        {
            //read next line, but do not write
            in.getline(c,20);
        }
        else
        {
            //write new info into temp.txt
            QString s = LevelManager::getUserName();
            out << s.begin() << endl;
            out << LevelManager::getLastUnlockedLevel() << endl;
        }
    }

    in.close();
    remove("saveFile.txt");
    out.close();
    rename("tempFile.txt","saveFile.txt");
}

//the current code only writes to the file. will build the file into high pile of all scores ever gained in games
void LevelManager::saveHighScore() {
    ofstream os("HighScore.txt");

    //write out name
    os << LevelManager::getUserName().cbegin() << ":" << endl << endl;

    //write out highscore
    os << getUserHighScore();

    //close file
    os.close();

/* THIS CODE EXTRACTS VALUES, ORGANIZES THEM, AND THEN OUTPUTS THEM TO THE FILE

 //WARINGING: THIS CODE ASSUMES VALUES IN THE HIGHSCORE FILE; WILL PROBABLY PUT IN FALSE VALUES FOR USER TO COMPETE AGAINST

class
{
    QString name;
    int HighScore;

public: //getters and setters

}

vector<class> vec;
char c[20];
ifstream in("saveFile.txt");

//load the contents of the file into a vector of comparing with new values
for (int i = 0; i < 5; i++)
{
    class cl = new class();

    in.getline(c, 20);

    cl.setName(QString(c));

    in.getline(c, 20);

    cl.setHighScore(*c); //need one setter to take a pointer

    vec.push_back(cl);
}

auto counter = vec.begin();
class cl;

//search through every element
for (element : vec)
{
    //if an element is smaller, then create a new class
    if(element.getName() < LevelManager::getUserName())
    {
        cl = new class();
        cl.setName(LevelManager::getUserName());
        cl.setHighScore(LevelManager::getHighScore()); // need another setter to take a simple int variable

        //this line will explode if the userScore is higher than the highest score.
        vec.insert(counter - 1, cl); //FIND A WAY TO INSERT CODE AT THE BEGINNING OF A VECTOR OR LEAVE THE FIRST ELEMENT OPEN SO THAT AN ELEMENT MAY BE INSERTED THERE.
    }
    ++counter;
}

//write the elements to a new HighScore.txt

//destroy the vector and delete elements

*/
}

//attempts to load a saved lastUnlockedLevel by comparing username to saveFile.txt
//if found, then sets the static lastUnlockedLevel for use by the LevelLoading method
//if returns false then program can start a new game.
void LevelManager::loadFile() {
    //to convert the char *a to a string
    stringstream s;

    //open file for reading
    ifstream fs("saveFile.txt");
    char a[20];

    //check if file open
    if(fs.is_open() == true) {
        //keep going till end of file
        while (!fs.peek()==EOF) {
            //read line of file, which should be a name
            fs.getline(a, 20);

            //if name equals userName, then load lastUnlockedLevelber and end loop
            if(LevelManager::getUserName() == QString(a)) {
                //since we found user name, then read the user's lastUnlockedLevel
                fs.getline(a, 20);

                //convert to number
                int i = *a;

                //load number into
                LevelManager::setLastUnlockedLevel(i);

                //close file
                fs.close();

            //if the name in the file is not what i want, then throw away the lastUnlockedLevel
            } else if (LevelManager::getUserName() != QString(a)){
                fs.getline(a, 20);
            }
        }
    }
    //set lastUnlockedLevel
    LevelManager::setLastUnlockedLevel(1);
}

