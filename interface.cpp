#include "interface.h"
#include "levelmanager.h"
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>

Interface::Interface() {}

Interface Interface::instance;

Ui::MainWindow* Interface::ui;

Interface Interface::getInstance() {
    return instance;
}

void Interface::setUi(Ui::MainWindow *initUi) {
    ui = initUi;
}

void Interface::drawObject(LevelObject* obj) {
    int id = obj->getId();
    QWidget* area = (ui->gameArea);
    QLabel* lbl = new QLabel(area);
    lbl->setText(QString::number(id));
    lbl->setGeometry(obj->getGeometry());
    lbl->setStyleSheet("QLabel {color:red; background-color: red;}");
    lbl->show();
}

void Interface::moveObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->text() == QString::number(obj->getId())) {
            //correct label
            //move the label to the new position
            lbl->setGeometry(obj->getGeometry());
        }
    }
}

void Interface::deleteObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->text() == QString::number(obj->getId())) {
            //correct label
            //hide and then delete the label
            lbl->hide();
            lbl->deleteLater();
        }
    }
}

void Interface::showTime(QString str) {
    ui->timeLeft->setText(str);
}

void Interface::showVictory() {
    //bool vic = LevelManager::getInstance().getVictory();
    //if (vic == true){
        QMessageBox *banner = new QMessageBox(ui->gameArea);

        if(LevelManager::getInstance().getLevel() < 9){
            banner->setText("Congratulations. You've completed this mission soldier.\n\n\n  ---New Mission Unlocked---");
            banner->show();
        }
        else{
            banner->setText("Mission accomplished, soldier! You've done your country proud.");
            banner->show();
        }
        int lvl = (LevelManager::getInstance().getLevel() + 1);
        if(lvl < LevelManager::getLastUnlockedLevel()){}
        else{
        LevelManager::getInstance().setLastUnlockedLevel(lvl);
        if(LevelManager::getInstance().getLastUnlockedLevel() == 2){ui->bt2->setEnabled(true);}
    }
  //}
}

void Interface::howTo(){
    QMessageBox *explain = new QMessageBox(ui->gameArea);
    explain->setText("Before playing, please insert your name in the box above and hit load to begin your campaign.\nThis is a simple overview of the game's controls.\nControls:\n\n -Right arrow moves the tank right.\n -Down arrow moves the tank down.\n -Left arrow moves the tank left.\n -Up arrow moves the tank up.\n -Click the mouse on the playing field to shoot.\nNOTE: Your bullets will follow the mouse's current position.\n\nTo beat the game, simply be the last tank standing. Good luck.");
    explain->show();
}

void Interface::showDefeat(QString msg){
    QMessageBox *banner = new QMessageBox(ui->gameArea);
    banner->setText(msg);
    banner->show();

}
