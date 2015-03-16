#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
//    QTimer *timer = new QTimer(this);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer* getTimer();

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
    //void on_rbEasy_clicked();
    //void on_rbMedium_clicked();
    //void on_rbHard_clicked();
};

#endif // MAINWINDOW_H
