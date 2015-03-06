#include "interface.h"
#include <QString>
#include <QStyle>

Interface::Interface() {}

Interface Interface::instance;

Interface Interface::getInstance() {
    return instance;
}

void Interface::setUi(Ui::MainWindow *initUi) {
    ui = initUi;
}

void Interface::drawObject(LevelObject* obj) {
    int id = obj->getId();
    MovableLabel* lbl = new MovableLabel(ui->mainArea);
    lbl->setText(QString::number(id));
    lbl->setGeometry(obj->getGeometry());
    QStyle* style = new QStyle();
    style->setProperty("background-color", "red");
    style->setProperty("color", "red");
    lbl->setStyle(style);
    lbl->show();
}

void Interface::moveObject(LevelObject *obj) {
    for(QObject* obj2: ui->mainArea->children()) {
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
    for(QObject* obj2: ui->mainArea->children()) {
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

void Interface::setTimeLeft(QString time) {
    //TODO: create the label and set it here
}
