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

void MainWindow::on_pbLoad_clicked()
{
    //void all buttons beforehand so a new lastUnlockedLevel may take effect
    ui->bt1->setEnabled(false);
    ui->bt2->setEnabled(false);
    ui->bt3->setEnabled(false);
    ui->bt4->setEnabled(false);
    ui->bt5->setEnabled(false);
    ui->bt6->setEnabled(false);
    ui->bt7->setEnabled(false);
    ui->bt8->setEnabled(false);
    ui->bt9->setEnabled(false);
    
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
    if(LevelManager::getLastUnlockedLevel() > 1) {ui->bt1->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 2) {ui->bt2->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 3) {ui->bt3->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 4) {ui->bt4->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 5) {ui->bt5->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 6) {ui->bt6->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 7) {ui->bt7->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 8) {ui->bt8->setEnabled(true); }
    if(LevelManager::getLastUnlockedLevel() > 9) {ui->bt9->setEnabled(true); }

    //find code to display changes to screen
}

void MainWindow::on_bt1_clicked()
{
    LevelManager::getInstance().loadLevel(1);
}

void MainWindow::on_bt2_clicked()
{
    LevelManager::getInstance().loadLevel(2);
}

void MainWindow::on_bt3_clicked()
{
    LevelManager::getInstance().loadLevel(3);
}

void MainWindow::on_bt4_clicked()
{
    LevelManager::getInstance().loadLevel(4);
}

void MainWindow::on_bt5_clicked()
{
    LevelManager::getInstance().loadLevel(5);
}

void MainWindow::on_bt6_clicked()
{
    LevelManager::getInstance().loadLevel(6);
}

void MainWindow::on_bt7_clicked()
{
    LevelManager::getInstance().loadLevel(7);
}

void MainWindow::on_bt8_clicked()
{
    LevelManager::getInstance().loadLevel(8);
}

void MainWindow::on_bt9_clicked()
{
    LevelManager::getInstance().loadLevel(9);
}
