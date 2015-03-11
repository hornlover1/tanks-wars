#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
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
    /*
    void on_bt1_clicked();
    void on_bt2_clicked();
    void on_bt3_clicked();
    void on_bt4_clicked();
    void on_bt5_clicked();
    void on_bt6_clicked();
    void on_bt7_clicked();
    void on_bt8_clicked();
    void on_bt9_clicked();
    */
};

#endif // MAINWINDOW_H
