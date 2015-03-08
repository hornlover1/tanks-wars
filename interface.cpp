#include "interface.h"
#include <QString>
#include <QStyle>
#include <QCommonStyle>

Interface::Interface() {}

Interface Interface::instance;

Ui::MainWindow* Interface::ui;

Interface Interface::getInstance() {
    return instance;
}

void Interface::setUi(Ui::MainWindow *initUi) {
    Interface::ui = initUi;
}

void Interface::drawObject(LevelObject* obj) {
    int id = obj->getId();
    MovableLabel* lbl = new MovableLabel(ui->gameArea);
    lbl->setText(QString::number(id));
    lbl->setGeometry(obj->getGeometry());
    QStyle* style = new QCommonStyle();
    style->setProperty("background-color", "red");
    style->setProperty("color", "red");
    lbl->setStyle(style);
    lbl->show();
}

void Interface::moveObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        MovableLabel* lbl = dynamic_cast<MovableLabel*>(obj2);
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
        MovableLabel* lbl = dynamic_cast<MovableLabel*>(obj2);
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

void Interface::setTimeLeft(QString /*time*/) {
    //TODO: create the label and set it here
}
