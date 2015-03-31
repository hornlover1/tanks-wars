#include "filemanager.h"
#include "levelmanager.h"
#include "userinformation.h"

FileManager::FileManager(QObject *parent): QObject(parent) {
}

FileManager FileManager::instance;

FileManager& FileManager::getInstance() {
    return instance;
}

//writes userName and lastUnlockedLevel to a file. Accounts for previous saves.
void FileManager::saveFile() {

    if(UserInformation::getInstance().getUserName() == "") {
        UserInformation::getInstance().setUserName("UNKNOWN");
    }
    //c_string to read bytes into
    char c[20];

    //open the current saveFile
    ifstream in("saveFile.txt");

    //create a new file to write data into
    ofstream out("tempFile.txt");

    //write new info into temp.txt
    QString s = UserInformation::getUserName();
    out << s.toStdString().c_str() << endl;
    out << UserInformation::getLastUnlockedLevel() << endl;

    //loop through every line in file
    do {
        //read data and put into a QString for comparison
        in.getline(c,20);
        QString info = QString(c);

        //if line not the userName
        if(info != UserInformation::getUserName()) {
            //write this line and the next one
            out << c << endl;

            in.getline(c,20);

            out << c << endl;
        //if line is userName, then do not write this line
        } else if(info == UserInformation::getUserName()) {
             //read next line, but do not write
            in.getline(c,20);
        }
    } while(in.peek() != EOF);

    in.close();
    out.close();
    remove("saveFile.txt");
    rename("tempFile.txt","saveFile.txt");
}

//saves new HighScore; assumes an existing HighScore.txt
void FileManager::saveUserHighScore() {
    if(UserInformation::getInstance().getUserName() == "") {
        UserInformation::getInstance().setUserName("UNKNOWN");
    }

    char c[20];
    ofstream outStream("temp.txt");
    QString filename = QString("highscore") + QString::number(UserInformation::getInstance().getLevel()) + QString(".txt");
    ifstream inStream(filename.toStdString().c_str());

    inStream.getline(c,20);//disregard first name
    int counter = 0; //counts how many levels in the userHighScore will be put
    bool isInserted = false; //determines whether highscore was inserted

    while(inStream.peek() != EOF) {
        inStream.getline(c,20); //grab number

        //acurately change c_string to number
        string stringValue = string(c);
        stringstream conversion (stringValue);
        int number = 0;
        conversion >> number;

        //int number = *c; //appears to convert to askii characters, cause it ain't grabbing the correct number

        if (UserInformation::getInstance().getUserHighScore() > number) {
            isInserted = true;
            //reset stream state to start from clean slate
            inStream.close();
            inStream.open(filename.toStdString().c_str());

            int i = 0; //this value keeps track of how many sets of insertions have been made to temp.txt
            while (i < counter) {//while temp does not have as many sets of insertions as highscore.txt keep inputing
                for(int integer = 0; integer < 3; integer++) {//input a set {username, highscore, blank space}
                    inStream.getline(c,20);
                    outStream << c << endl; //I assume this will write the whole line, no more no less
                }
                i++;
            }

            //write new highScore
            outStream << UserInformation::getUserName().toStdString().c_str() << endl;
           // userHighScore = Interface::getInstance().getTimeLeft();
            outStream << UserInformation::getInstance().getUserHighScore();
            outStream << endl << endl;
            i++;

            while(i < 5) {
                for(int integer = 0; integer < 3; integer++) {
                    inStream.getline(c,20);
                    outStream << c << endl; //I assume this will write the whole line, no more no less
                }
                i++;
                //break;
            }
            break;
        } else {
            inStream.getline(c,20); //chuck out empty whitespace
            inStream.getline(c, 20); //chuck out the next name so we can get the number later
        }

        counter++; //this goes up every time a set of data is read. {name, highscore, whiteSpace}
    }

    inStream.close();
    outStream.close();

    if (isInserted == true) {
        remove("HighScore.txt");
        //QString filename = QString("HighScore") + QString::number(levelNumber) + QString(".txt");
        rename("temp.txt", filename.toStdString().c_str());
    } else {
        remove("temp.txt");
    }
}

void FileManager::loadFile() {
    //flag if name not found
    bool nameFound = false;

    //open file for reading
    ifstream fs("saveFile.txt");
    char a[20];

    //check if file open
    if(fs.is_open() == true) {
        //keep going till end of file
        while (fs.peek() != EOF) {
            //read line of file, which should be a name
            fs.getline(a, 20);

            //if name equals userName, then load lastUnlockedLevelber and end loop
            if(UserInformation::getUserName() == QString(a)) {
                nameFound = true;
                //since we found user name, then read the user's lastUnlockedLevel
                fs.getline(a, 20);

                //acurately change c_string to number
                string stringValue = string(a);
                stringstream conversion (stringValue);
                int i = 0;
                conversion >> i;

                //load number into
                UserInformation::setLastUnlockedLevel(i);

                //close file
                fs.close();
                break;

            //if the name in the file is not what i want, then throw away the lastUnlockedLevel
            } else if (UserInformation::getInstance().getUserName() != QString(a)){
                fs.getline(a, 20);
            }
        }
    }
    if(nameFound == false){
        //set lastUnlockedLevel
        UserInformation::setLastUnlockedLevel(1);
    }
}
