//--------------------------------------------------------------
// File:   mainwindow.h
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file contains access to the gui, as well as
//      updating the gui when events happen in game, such as a
//      key press, mouse click, or button click.
//--------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
//    QTimer *timer = new QTimer(this);
    QTimer *timer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void on_pbLoad_clicked();
    void levelButtonClicked();
    void on_btCheat_clicked();
    void on_pushButton_2_clicked();
    void updateTime();
    void driveAI();
    void connectToClient();
    void startTimer() { timer->start(); }
};

#endif // MAINWINDOW_H
