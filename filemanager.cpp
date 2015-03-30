#include "filemanager.h"

FileManager::FileManager(QObject *parent): QObject(parent) {
}

FileManager FileManager::instance;

FileManager& FileManager::getInstance() {
    return instance;
}

