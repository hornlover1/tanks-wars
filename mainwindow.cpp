#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelmanager.h"
#include "interface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Interface::getInstance().setUi(ui);
    LevelManager::getInstance().loadLevel(1);
    qApp->installEventFilter(this);
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
    LevelManager::getInstance().mouseClick();
}

Direction getDirection(int key) {
    Direction d;
    switch (key) {
    case 37: d = West;  break; // left  key
    case 38: d = North; break; // up    key
    case 39: d = East;  break; // right key
    case 40: d = South; break; // down  key
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

void MainWindow::on_pbLoad_clicked()
{
    QString name = ui->leUserName->text();

    name.toUpper();

    //LevelManager::s
}
