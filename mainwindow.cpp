#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelmanager.h"
#include "interface.h"
#include "levelobject.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)) {
    ui->setupUi(this);
    Interface::getInstance().setUi(ui);

    timer->setInterval(1000);

    //this timer will decrement the time selected by the user
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    Interface::getInstance().blankUI();
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

void MainWindow::on_pbLoad_clicked() {
    //safety check if user put in a name

    //get the name
    QString name = ui->leUserName->text();

    name = name.toUpper();

    LevelManager::setUserName(name);

    //check for a savedfile. if found values will be set. if not
    //will use default values
    LevelManager::getInstance().loadFile();

    //free up the buttons based on lastUnlockedLevel so
    //that the player may start a game by selecting that button.
    //and stop repetitive coding
    for (QObject* obj: ui->levels->children()) {
        QPushButton* button = dynamic_cast<QPushButton*>(obj);
        if (button != nullptr) {
            if (button->text().toInt() <= LevelManager::getLastUnlockedLevel()) {
                button->setEnabled(true);
            } else {
                button->setEnabled(false);
            }
            connect(button, SIGNAL(clicked()), this, SLOT(levelButtonClicked()));
        }
        ui->leUserName->setEnabled(false);
    }
}

void MainWindow::levelButtonClicked() {
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if (button != nullptr) {
        Interface::getInstance().setUi(ui);
        int levelNum = button->text().toInt();
        LevelManager::getInstance().loadLevel(levelNum);
        qApp->installEventFilter(this);

        //disenable certain wiki's
        ui->leUserName->setEnabled(false);
        ui->btCheat->setEnabled(false);

        //load user time choice into code
        if(ui->rbEasy->isChecked() == true) {
            LevelManager::getInstance().selectTime(ui->rbEasy->text());
        } else if(ui->rbMedium->isCheckable() == true) {
            LevelManager::getInstance().selectTime(ui->rbMedium->text());
        } else if (ui->rbHard->isCheckable() == true) {
            LevelManager::getInstance().selectTime(ui->rbHard->text());
        }

        //start the timer counting down till user defeat
        timer->start();
        if (!ui->rbEasy->isChecked()) { ui->rbEasy->setEnabled(false); }
        if (!ui->rbMedium->isChecked()) { ui->rbMedium->setEnabled(false); }
        if (!ui->rbHard->isChecked()) { ui->rbHard->setEnabled(false); }
    }
}

//enables testing of ideas
void MainWindow::on_btCheat_clicked() {
    LevelManager::getInstance().loadLevel(0);
    qApp->installEventFilter(this);
    ui->leUserName->setEnabled(false);
    ui->rbEasy->setEnabled(false);
    ui->rbHard->setEnabled(false);
//    ui->rbMedium->setEnabled(false);
    ui->gameArea->setMouseTracking(true);
    ui->gameArea->installEventFilter(this);
    timer->start();
}

void MainWindow::updateTime() {
    if(LevelManager::getInstance().getStopTimer() == true) {
        timer->stop();
       // LevelManager::getInstance().setFinalGameTime();
        for(LevelObject* obj : LevelManager::getInstance().getObjects())
        {
            obj->pause();
        }
    } else {
        LevelManager::getInstance().decrementTime();
    }
}

void MainWindow::on_pushButton_2_clicked() {
    Interface::getInstance().howTo();
}

