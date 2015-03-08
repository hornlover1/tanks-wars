#include <QPainter>
#include <QRect>
#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelmanager.h"
#include "interface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    LevelManager::getInstance().loadLevel(1);
    qApp->installEventFilter(this);
    Interface::getInstance().setUi(ui);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        int mouseX = cursor().pos().x() - ui->gameArea->pos().x();
        int mouseY = cursor().pos().y() - ui->gameArea->pos().y();
        LevelManager::getInstance().moveMouse(mouseX, mouseY);
    } else if (event->type() == QEvent::MouseButtonPress) {
        LevelManager::getInstance().mouseClick();
    } else if (event->type() == QEvent::KeyPress) {
        QKeyEvent* ev = dynamic_cast<QKeyEvent*>(event);
        int key = ev->key();
        Direction d;
        switch (key) {
        case 37: d = West;  break; // left  key
        case 38: d = North; break; // up    key
        case 39: d = East;  break; // right key
        case 40: d = South; break; // down  key
        }
        if (key < 37 or key > 40) {
            return true;
        }
        LevelManager::getInstance().keyPress(d);
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* ev = dynamic_cast<QKeyEvent*>(event);
        int key = ev->key();
        Direction d;
        switch (key) {
        case 37: d = West;  break; // left  key
        case 38: d = North; break; // up    key
        case 39: d = East;  break; // right key
        case 40: d = South; break; // down  key
        }
        if (key < 37 or key > 40) {
            return true;
        }
        LevelManager::getInstance().keyRelease(d);
    }
    return true;
}

//TODO: write this file to call levelManager
