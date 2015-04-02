#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QObject>

#include <fstream>
#include <sstream>
using namespace std;

class UserInformation : public QObject {
    Q_OBJECT
    UserInformation(QObject *parent = 0);
    static UserInformation instance;

    //counter to record which level is available
    static int lastUnlockedLevel;

    //The name of the user
    QString userName = "";

    //current high score of the user
    int userHighScore;

    //used to find the correct level file to save the highScores to
    int levelNumber;

    //the time selected by the user
    QString userTime;

public:
    static UserInformation& getInstance();

    //getter and setter for the time selected by the user
    QString getUserTime();
    void selectTime(QString s);

    void setLevelNumber(int levelNum);

    //returns which level the user was playing
    int getLevel();

    //set userHighScore
    void setHighScore();

    //returns userHighScore
    int getUserHighScore();

    //get the username
    static QString getUserName();

    //set the username
    static void setUserName(QString name);

    //increment levelUnlockedLevel
    static void incrementLastUnlockedLevel();

    //code used by the load method to set the variable.
    static void setLastUnlockedLevel(int i);

    static int getLastUnlockedLevel();

signals:

public slots:

};

#endif // USERINFORMATION
