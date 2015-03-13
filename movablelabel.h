//--------------------------------------------------------------
// File:   movablelabel.h
// Author: Nathan Collins  Login: ncoll943  Class: CpS 111
// Desc: This extends a QLabel and allows the user to drag it around
//--------------------------------------------------------------
#ifndef MOVABLELABEL_H
#define MOVABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class MovableLabel : public QLabel {
    QWidget* win;
    bool mouseDragging;
    QPoint offset;
public:
    MovableLabel(QWidget* parent);
    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
};

#endif // MOVABLELABEL_H
