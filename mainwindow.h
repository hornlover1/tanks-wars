#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
//    QTimer *timer = new QTimer(this);
    QTimer *timer;

    //code to create sound
<<<<<<< HEAD
    //QMediaPlayer* player;// = new QMediaPlayer;
    //QMediaPlaylist *playlist = new QMediaPlaylist;
    QMediaPlayer* player;// = new QMediaPlayer;
    QMediaPlaylist *playlist;// = new QMediaPlaylist;



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
    void playTheList();
    void connectToClient();
    void startTimer() {
        timer->start();
    }
};

#endif // MAINWINDOW_H
