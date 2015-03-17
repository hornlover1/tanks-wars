#include "levelmanager.h"
#include "interface.h"
#include <QFile>
#include <QTextStream>
#include <math.h>
#include <cassert>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

QString LevelManager::userName = "";

int LevelManager::lastUnlockedLevel = 1;

LevelManager::LevelManager() {
    userTime = "Easy";
}

LevelManager LevelManager::instance;

int LevelManager::getEasyTime() {return easyTime;}
int LevelManager::getMediumTime() {return mediumTime;}
int LevelManager::getHardTime() {return hardTime;}

void LevelManager::decrementEasyTime() {easyTime--;}
void LevelManager::decrementMediumTime() {mediumTime--;}
void LevelManager::decrementHardTime() {hardTime--;}
void LevelManager::setBullet_obj(bool x) {bullet_obj = x;}

//called by a QTimer to decremented the user's selected time
void LevelManager::decrementTime() {
    if (easyTime <= 0 || mediumTime <= 0 || hardTime <= 0) {
        //TODO:stop game
        return;
    }
    if (userTime == "Easy") {
        easyTime--;
        Interface::getInstance().showTime(QString::number(easyTime));
    } else if(userTime == "Medium") {
        mediumTime--;
        Interface::getInstance().showTime(QString::number(mediumTime));
    } else if (userTime == "Hard") {
        hardTime--;
        Interface::getInstance().showTime(QString::number(hardTime));
    }

    if (easyTime == 0 || mediumTime == 0 || hardTime == 0) {
        Interface::getInstance().showDefeat("Sorry, time up.");
    }
}

void LevelManager::selectTime(QString s)
{
    userTime = s;
}
/*
void LevelManager::setUserHighScore() {
    LevelManager::userHighScore = 15 * finalGameTime;
}*/

int LevelManager::getUserHighScore() {
    return userHighScore;
}

void LevelManager::setHighScore()
{
    if(userTime == "Easy")
    {
        userHighScore = 10 * easyTime;
    }
    else if(userTime == "Medium")
    {
        userHighScore = 15 * mediumTime;
    }
    else if (userTime == "Hard")
    {
        userHighScore = 20 * hardTime;
    }
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

void LevelManager::setStopTimer(bool b)
{
    stopTimer = b;
}

bool LevelManager::getStopTimer() {return stopTimer;}
int LevelManager::getLevel() {return levelNumber;}

void LevelManager::loadLevel(int levelNum) {
    for (LevelObject* obj: objectsInLevel) {
        Interface::getInstance().deleteObject(obj);
        delete obj;
    }
    //start the timer back up again so that the countdown works
    stopTimer = false;

    objectsInLevel.clear();
    //bool bullet_obj = false;
    //Jordan's line
    levelNumber = levelNum; //i need this number for saveHighScore()

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

            qDebug() << "x" << x << "y" << y << "w" << width << "h" << height;

            LevelObject* obj = new WallObject(x, y, width, height);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if (argType == "tank") {
            int x, y;
            strm >> x >> y;

            qDebug() << "x" << x << "y" << y;

            LevelObject* obj = new TankObject(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if (argType == "tank2") {
            int x, y;
            strm >> x >> y;

            qDebug() << "x" << x << "y" << y;

            LevelObject* obj = new Target(x, y);
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
        Target* target = dynamic_cast<Target*>(obj);
        if (tank == nullptr || target != nullptr) {
            continue;
        }
        double diffX = mouseX - tank->getX();
        double diffY = mouseY - tank->getY();
        double heading = atan(diffY/diffX);
        double pi = 3.14159265358979323846264338327950288419716;
        if (diffX <= 0) {
            heading += pi; // add pi to rotate it 180 degrees so that it shoots in the right direction
        }
        if(bullet_obj == false){
        BulletObject* Bobj = new BulletObject(tank->getX(), tank->getY(), heading, tank);
        objectsInLevel.push_back(Bobj);
        setBullet_obj(true);
        Interface::getInstance().drawObject(Bobj);
        Bobj->startMotion();
        }
        else{}
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
        Target* target = dynamic_cast<Target*>(obj);
        if (tank == nullptr || target != nullptr) {
            //We're looking for the tank, not the tank2
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
    ifstream in("://Resources/saveFile.txt");

    //create a new file to write data into
    ofstream out("://Resources/tempFile.txt", ios_base::out);

    //write new info into temp.txt
    QString s = LevelManager::getUserName();
    out << s.begin() << endl;
    out << LevelManager::getLastUnlockedLevel() << endl;

    //loop through every line in file
    while(in.peek() != EOF);
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
        else if(info == LevelManager::getUserName())
        {
            //read next line, but do not write
            in.getline(c,20);
        }
    }

    in.close();
    out.close();
    remove("://Resources/saveFile.txt");
    rename("://Resources/tempFile.txt","://Resources/saveFile.txt");
}

//saves new HighScore; assumes an existing HighScore.txt
//currently stores only the 5 highest scores in the whole game
void LevelManager::saveUserHighScore() {

    char c[20];
    ofstream outStream("temp.txt");
    QString filename = QString("highscore") + QString::number(levelNumber) + QString(".txt");
    ifstream inStream(filename.toStdString().c_str());

    inStream.getline(c,20);//disregard first name
    int counter = 0; //counts how many levels in the userHighScore will be put
    bool isInserted = false; //determines whether highscore was inserted

    while(inStream.peek() != EOF)
    {
        inStream.getline(c,20); //grab number

        //acurately change c_string to number
        string stringValue = string(c);
        stringstream conversion (stringValue);
        int number = 0;
        conversion >> number;

        //int number = *c; //appears to convert to askii characters, cause it ain't grabbing the correct number

        if (userHighScore > number)
        {
            isInserted = true;
            //reset stream state to start from clean slate
            inStream.close();
            inStream.open(filename.toStdString().c_str());

            int i = 0; //this value keeps track of how many sets of insertions have been made to temp.txt
            while (i < counter) //while temp does not have as many sets of insertions as highscore.txt keep inputing
            {
                for(int integer = 0; integer < 3; integer++) //input a set {username, highscore, blank space}
                {
                    inStream.getline(c,20);
                    outStream << c << endl; //I assume this will write the whole line, no more no less
                }
                i++;
            }

            //write new highScore
            outStream << LevelManager::getUserName().toStdString().c_str() << endl;
           // userHighScore = Interface::getInstance().getTimeLeft();
            outStream << userHighScore;
            outStream << endl << endl;
            i++;

            while(i < 5)
            {
                for(int integer = 0; integer < 3; integer++)
                {
                    inStream.getline(c,20);
                    outStream << c << endl; //I assume this will write the whole line, no more no less
                }
                i++;
                //break;
            }
            break;
        }
        else
        {
            inStream.getline(c,20); //chuck out empty whitespace
            inStream.getline(c, 20); //chuck out the next name so we can get the number later
        }

        counter++; //this goes up every time a set of data is read. {name, highscore, whiteSpace}
    }

    inStream.close();
    outStream.close();

    if (isInserted == true)
    {
        remove("HighScore.txt");
        //QString filename = QString("HighScore") + QString::number(levelNumber) + QString(".txt");
        rename("temp.txt", filename.toStdString().c_str());
    }
    else
    {
        remove("temp.txt");
    }
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

void LevelManager::fireBullet(int x, int y, int heading, TankObject* tank) {
    BulletObject* Bobj = new BulletObject(x, y, heading, tank);
    objectsInLevel.push_back(Bobj);
    Interface::getInstance().drawObject(Bobj);
    Bobj->startMotion();
}


