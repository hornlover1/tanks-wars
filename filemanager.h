#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class FileManager : public QObject {
    Q_OBJECT
    FileManager(QObject *parent = 0);
    static FileManager instance;


public:
    static FileManager& getInstance();

signals:
    
public slots:
    
};

#endif // FILEMANAGER_H
