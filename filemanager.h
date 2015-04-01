#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include <fstream>
#include <sstream>
using namespace std;

class FileManager : public QObject {
    Q_OBJECT
    FileManager(QObject *parent = 0);
    static FileManager instance;


public:
    static FileManager& getInstance();

    //save game to a file
    void saveFile();

    //save highscore to a file
    void saveUserHighScore();

    //read in the saved file
    void loadFile();
};

#endif // FILEMANAGER_H
