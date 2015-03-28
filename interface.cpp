#include "interface.h"
#include "levelmanager.h"
#include <cstring>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>

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
    for (QObject* obj: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj);
        if (lbl != nullptr && lbl->width() == 800 and lbl->height() == 600) {
            lbl->hide();
            lbl->deleteLater();
        }
    }
    int id = obj->getId();
    QWidget* area = (ui->gameArea);
    QLabel* lbl = new QLabel(area);
    lbl->setGeometry(obj->getGeometry());
    lbl->setAccessibleName(QString::number(id)); //the loaded id will be used to link the label with its code instantiation

    //code to load images to labels
    QPixmap pic(obj->getImagePath().toStdString().c_str());
    lbl->setPixmap(pic);
    lbl->setScaledContents(true);

  //  lbl->setStyleSheet("QLabel {color:red; background-color: red;}");
    lbl->show();
}

void Interface::moveObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->accessibleName() == QString::number(obj->getId())) {
            //correct label
            //move the label to the new position,

            //make it face the right direction - may go into own class

            TankObject* TankObj = dynamic_cast<TankObject*>(obj);
            if(TankObj != nullptr) {
                lbl->setGeometry(TankObj->getGeometry());

                QPixmap pixmap(*lbl->pixmap());
                QMatrix rm;

                int degrees = getDegrees(TankObj);

                rm.rotate(degrees);
                pixmap = pixmap.transformed(rm);
                lbl->setPixmap(pixmap);
            } else {
                lbl->setGeometry(obj->getGeometry());
            }
        }
    }
}

int Interface::getDegrees(TankObject* obj) {
    int degrees = 0;
    if (obj->getDirectionFaced() == obj->getD()){
            degrees = 0;
       }

   else if (obj->getDirectionFaced() == North){
       switch (obj->getD()) {
           case East: degrees = 90; obj->setDirectionFaced(East); break;
           case South: degrees = 180; obj->setDirectionFaced(South); break;
           case West: degrees = -90; obj->setDirectionFaced(West); break;
       }
    }
   else if (obj->getDirectionFaced() == West){
       switch (obj->getD()) {
           case East: degrees = 180; obj->setDirectionFaced(East); break;
           case South: degrees = -90; obj->setDirectionFaced(South); break;
           case North: degrees = 90; obj->setDirectionFaced(North); break;
       }
    }

   else if (obj->getDirectionFaced() == South){
       switch (obj->getD()) {
           case East: degrees = -90; obj->setDirectionFaced(East); break;
           case North: degrees = 180; obj->setDirectionFaced(North); break;
           case West: degrees = 90; obj->setDirectionFaced(West); break;
       }
    }

   else if (obj->getDirectionFaced() == East){
       switch (obj->getD()) {
           case North: degrees = -90; obj->setDirectionFaced(North); break;
           case West: degrees = 180; obj->setDirectionFaced(West); break;
           case South: degrees = 90; obj->setDirectionFaced(South); break;
       }
    }
   return degrees;
}

void Interface::deleteObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->accessibleName() == QString::number(obj->getId())) {
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
    blankUI();
    QMessageBox *banner = new QMessageBox(ui->gameArea);

        //display the message
        banner->setText("Congratulations. You've completed this mission soldier.");
        banner->show();

        updateFiles();
        updateGUI();
}

void Interface::updateFiles()
{
    //prepare for next level
    if(LevelManager::getLastUnlockedLevel() == LevelManager::getInstance().getLevel())
    {
        LevelManager::getInstance().incrementLastUnlockedLevel();
    }

    LevelManager::getInstance().saveFile(); //works

    LevelManager::getInstance().setHighScore(); //works!

    LevelManager::getInstance().saveUserHighScore(); //works!
}

void Interface::updateGUI(){
    //unlock the next button on the GUI
    for (QObject* obj: ui->levels->children()) {
        QPushButton* button = dynamic_cast<QPushButton*>(obj);
        if (button != nullptr) {
            if (button->text().toInt() <= LevelManager::getLastUnlockedLevel()) {
                button->setEnabled(true);
            }
        }
     }

    //reset variables for next level
    ui->leUserName->setEnabled(true);
   // ui->rbEasy->setCheckable(true);
    ui->rbEasy->setEnabled(true);
//    ui->rbMedium->setCheckable(true);
    ui->rbMedium->setEnabled(true);
//    ui->rbHard->setCheckable(true);
    ui->rbHard->setEnabled(true);
    ui->btCheat->setEnabled(true);
    ui->opponentIp->setEnabled(true);
}

void Interface::howTo() {
    QMessageBox *explain = new QMessageBox(ui->gameArea);
    explain->setText("Before playing, please insert your name in the box above and hit load to begin your campaign.\nThis is a simple overview of the game's controls.\nControls:\n\n -Right arrow moves the tank right.\n -Down arrow moves the tank down.\n -Left arrow moves the tank left.\n -Up arrow moves the tank up.\n -Click the mouse on the playing field to shoot.\nNOTE: Your bullets will follow the mouse's current position.\n\nTo beat the game, simply be the last tank standing. Good luck.");
    explain->show();
}

void Interface::showDefeat(QString msg) {
    blankUI();
    QMessageBox *banner = new QMessageBox(ui->gameArea);
    banner->setText(msg);
    banner->show();

    updateGUI();
}

void Interface::blankUI() {
    for (QObject* obj: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj);
        if (lbl != nullptr) {
            lbl->hide();
            lbl->deleteLater();
        }
    }
    QLabel* lbl = new QLabel(ui->gameArea);
    lbl->setGeometry(0, 0, 800, 600); // fill up the screen
    lbl->setScaledContents(true);
    QPixmap picture(":/Resources/logo.png");
    lbl->setPixmap(picture);
    lbl->show();
}

int Interface::getTimeLeft() {
    QString time = ui->timeLeft->text();
    int highscore = time.toInt();
    if(ui->rbEasy->isChecked()){
        highscore = highscore * 10;
    } else if(ui->rbMedium->isChecked()){
        highscore = highscore * 20;
    } else if(ui->rbHard->isChecked()){
        highscore = highscore * 30;
    }
    return highscore;
}
