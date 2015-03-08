#include "levelmanager.h"
#include "interface.h"
#include <QFile>
#include <QTextStream>

LevelManager::LevelManager(): timer(new QTimer) {
    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start();
}

LevelManager LevelManager::instance;
/*
void LevelManager::setUserHighScore(int score) {
    userHighScore = score;
}

int LevelManager::getUserHighScore() {
    return userHighScore;
}

int LevelManager::lastUnlockedLevel = 1;

QString LevelManager::getUserName() {
    return userName;
}

void LevelManager::setUserName(string name) {
       userName = name;
}

void LevelManager::incrementLastUnlockedLevel() {
    if(lastUnlockedLevel < 9){
        lastUnlockedLevel++;
    }
}

static void LevelManager::setLastUnlockedLevel(int i) {
  lastUnlockedLevel = i;
}

int LevelManager::getLastUnlockedLevel() {
    return lastUnlockedLevel;
}
*/
LevelManager& LevelManager::getInstance() {
    return instance;
}

vector<LevelObject*> LevelManager::getObjects() {
    return objectsInLevel;
}

void LevelManager::loadLevel(int levelNum) {
    for (LevelObject* obj: objectsInLevel) {
        delete obj;
    }
    objectsInLevel.clear();

    QFile levelX(":/Resources/level" + QString::number(levelNum));
    QTextStream strm(&levelX);

    QString argType;
    while (!(strm >> argType).atEnd()) {
        if (argType == "time") {
            strm >> easyTime >> mediumTime >> hardTime;
        } else if (argType == "wall") {
            int x, y, width, height;
            strm >> x >> y >> width >> height;
            LevelObject* obj = new WallObject(x, y, width, height);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        } else if (argType == "tank") {
            int x, y;
            strm >> x >> y;
            LevelObject* obj = new TankObject(x, y);
            objectsInLevel.push_back(obj);
            Interface::getInstance().drawObject(obj);
        }
    }
    //TODO: load the next level from file
}

void LevelManager::onTimeOut() {
    for (LevelObject* obj: objectsInLevel) {
        MovableObject* mv = dynamic_cast<MovableObject*>(obj);
        Interface::getInstance().moveObject(mv);
    }
}

void LevelManager::moveMouse(int x, int y) {
    mouseX = x;
    mouseY = y;
    //TODO: write logic to move the turret
}

void LevelManager::mouseClick() {
    //TODO: fire a bullet at the target
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
}

void LevelManager::keyRelease(Direction d) {
    //TODO: write this method
    //get tank
    //stop tank moving
}

LevelManager::~LevelManager() {
    delete timer;
}

/*
void LevelManager::saveFile() {
    //open/create the file
    ofstream fs("saveFile.txt");

    //write user name
    fs << "user.name \"" << LevelManager::getUserName() << "\"" << endl;

    //write last unlocked level
    fs << "maxLevel \"" << LevelManager::getLastUnlockedLevel() << "\"" << endl;

    //close file
    fs.close();
}

void LevelManager::saveHighScore() {
    ofstream os("HighScore.txt");

    //write out name
    os << LevelManager::getUserName() << ":" << endl << endl;

    //write out highscore
    os << getUserHighScore();

    //close file
    os.close();
}

//attempts to load a saved levelNumber by comparing username to saveFile.txt
//if found, then returns true so that an instance of the game can be called with
//that levelNumber
//if returns false then program can start a new game.
bool LevelManager::loadFile() {
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
            getLine(fs,a);

            //load into a stringsteam for easy manipulation
            s = a;

            //if name equals userName, then load levelNumber and end loop
            if(LevelManager::getUserName() == s.str()) {
                //since we found user name, then read the user's levelNumber
                getLine(fs, a);

                //convert a to a number - how? this work?
                s = a;
                int i = stoi(s.str());

                //load number into
                LevelManager::setLastUnlockedLevel(i);

                //close file
                fs.close();

                //return true so the program knows that the levelNumber was found
                return true;
            //if the name in the file is not what i want, then throw away the levelNumber
            } else if (!LevelManager::getUserName() == s.str()){
                getLine(fs, a);
            }
        }
    }
    //set levelNumber
    LevelManager::setLastUnlockedLevel(0);
    
    //if loop cannot find the name, then returns false so a new game can be created.
    return false;
}

int LevelManager::lastUnlockedLevel = 1;
*/
