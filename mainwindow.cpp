#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelmanager.h"
#include "interface.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Interface::getInstance().setUi(ui);
    LevelManager::getInstance().loadLevel(1);
    qApp->installEventFilter(this);
    ui->leUserName->setEnabled(false);
    ui->rbEasy->setEnabled(false);
    ui->rbHard->setEnabled(false);
//    ui->rbMedium->setEnabled(false);
    ui->gameArea->setMouseTracking(true);
    ui->gameArea->installEventFilter(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent*) {
    int mouseX = cursor().pos().x() - ui->gameArea->pos().x();
    int mouseY = cursor().pos().y() - ui->gameArea->pos().y();
    LevelManager::getInstance().moveMouse(mouseX, mouseY);
}

void MainWindow::mousePressEvent(QMouseEvent*) {
    qDebug() << "cursor x: " << cursor().pos().x() << ", gameArea x: " + ui->gameArea->pos().x();
    qDebug() << "cursor y: " << cursor().pos().y() << ", gameArea y: " + ui->gameArea->pos().y();
    int mouseX = cursor().pos().x() - 275;//ui->gameArea->pos().x();
    int mouseY = cursor().pos().y() - 208;//ui->gameArea->pos().y();
    LevelManager::getInstance().moveMouse(mouseX, mouseY);
    LevelManager::getInstance().mouseClick();
}

Direction getDirection(int key) {
    Direction d;
    switch (key) {
    case Qt::Key_Left:  d = West;  break; // left  key
    case Qt::Key_Up:    d = North; break; // up    key
    case Qt::Key_Right: d = East;  break; // right key
    case Qt::Key_Down:  d = South; break; // down  key
    }
    return d;
}

void MainWindow::keyPressEvent(QKeyEvent* ev) {
    int key = ev->key();
    Direction d = getDirection(key);
    LevelManager::getInstance().keyPress(d);
}

void MainWindow::keyReleaseEvent(QKeyEvent* ev) {
    int key = ev->key();
    Direction d = getDirection(key);
    LevelManager::getInstance().keyRelease(d);
}

//TODO: write this file to call levelManager
