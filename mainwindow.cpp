#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelmanager.h"
#include "interface.h"
#include "levelobject.h"
#include "networkmanager.h"

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

    QTcpServer* server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(connectToClient()));
    server->listen(QHostAddress::Any, 5000);

    NetworkManager::getInstance().startServer(this);
    ui->yourIP->setText("Your IP: " + NetworkManager::getInstance().getIp4Addr());

    connect(&NetworkManager::getInstance(), SIGNAL(startLevel()), this, SLOT(startTimer()));

    player = new QMediaPlayer;
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile(":/Resources/Sound/BattleMarch.mp3"));
    player->setVolume(50);
    player->play();

}

void MainWindow::connectToClient() {
    QMessageBox::information(this, "Hello", "connected");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent*) {
    int mouseX = cursor().pos().x() - ui->gameArea->geometry().topLeft().x();
    int mouseY = cursor().pos().y() - ui->gameArea->geometry().topLeft().y();
    LevelManager::getInstance().moveMouse(mouseX, mouseY);
}

void MainWindow::mousePressEvent(QMouseEvent*) {
    qDebug() << "cursor x: " << ui->gameArea->mapFromGlobal(cursor().pos()).x();
    qDebug() << "cursor y: " << ui->gameArea->mapFromGlobal(cursor().pos()).y();
    int mouseX = ui->gameArea->mapFromGlobal(cursor().pos()).x();
    int mouseY = ui->gameArea->mapFromGlobal(cursor().pos()).y();
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
    if(LevelManager::getInstance().getObjects().size() > 2){
        int key = ev->key();
        Direction d = getDirection(key);
        LevelManager::getInstance().keyPress(d);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* ev) {
    if(LevelManager::getInstance().getObjects().size() > 2){
        int key = ev->key();
        Direction d = getDirection(key);
        LevelManager::getInstance().keyRelease(d);
    }
}

//TODO: write this file to call levelManager

void MainWindow::on_pbLoad_clicked() {
    //safety check if user put in a name
 //get the name
    QString name = ui->leUserName->text();
    if(name.size() == 0)
    {
        QMessageBox::information(this, "Mistake", "Please input a username");
        return;
    }

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
        } else if(ui->rbMedium->isChecked() == true) {
            LevelManager::getInstance().selectTime(ui->rbMedium->text());
        } else if (ui->rbHard->isChecked() == true) {
            LevelManager::getInstance().selectTime(ui->rbHard->text());
        }

        ui->opponentIp->setEnabled(false);

        //start the timer counting down till user defeat
        timer->start();
        if (!ui->rbEasy->isChecked()) { ui->rbEasy->setEnabled(false); }
        if (!ui->rbMedium->isChecked()) { ui->rbMedium->setEnabled(false); }
        if (!ui->rbHard->isChecked()) { ui->rbHard->setEnabled(false); }
        if (ui->opponentIp->text() != "") {
            NetworkManager::getInstance().connectToHost(ui->opponentIp->text(), levelNum);
        } else {
            //timer will drive actions of AI
            //connect(timer, SIGNAL(timeout()), this, SLOT(driveAI()));
        }
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
    ui->opponentIp->setEnabled(false);
    timer->start();
}

void MainWindow::updateTime() {
    if(LevelManager::getInstance().getStopTimer() == true) {
        timer->stop();

        for(LevelObject* obj : LevelManager::getInstance().getObjects())
        {
            obj->pause();
        }
    } else {
        LevelManager::getInstance().decrementTime();
    }
}

void MainWindow::driveAI() {
    LevelManager::getInstance().AI();
}

void MainWindow::playTheList() {
    bool firstPass = false;
    if(firstPass == false) {
       // playlist->addMedia(QUrl::fromLocalFile(":/Resources/Sound/BattleMarch.mp3"));
        //playlist->setCurrentIndex(1);
/*
        player->setMedia(QUrl::fromLocalFile(":/Resources/Sound/BattleMarch.mp3"));
       // player->setPlaylist(playlist);
connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        player->setVolume(50);
        player->play();

        firstPass = true;
        */
    }
}

void MainWindow::on_pushButton_2_clicked() {
    Interface::getInstance().howTo();
}
