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

void Interface::showVictory()
{
    QMessageBox *banner = new QMessageBox(ui->gameArea);
    banner->setText("Good job. You've completed your mission, soldier.");
    banner->show();
}

void Interface::showDefeat(QString msg)
{
    QMessageBox *banner = new QMessageBox(ui->gameArea);
    banner->setText(msg);
    banner->show();
}
