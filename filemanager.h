//--------------------------------------------------------------
// File:   filemanager.h
// Author: Jordan Fleck  Team: Barnabas  Class: CpS 111
// Desc: This file is in charge of keeping track of the highscore
//      and save files for the game.
//--------------------------------------------------------------

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
    //The instance
    static FileManager& getInstance();

    //save game to a file
    void saveFile();

    //save highscore to a file
    void saveUserHighScore();

    //read in the saved file
    void loadFile();
};

#endif // FILEMANAGER_H
