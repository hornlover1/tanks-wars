//--------------------------------------------------------------
// File:   networkmanager.cpp
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file manages the connection to other players
//      for mulitplayer gameplay.
//--------------------------------------------------------------

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <sstream>
#include <QApplication>

#include "networkmanager.h"
#include "opponentmanager.h"
#include "interface.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent), port(7573), remotePort(7573) {
    sock = nullptr;
    for (QHostAddress host: QNetworkInterface::allAddresses()) {
        if (host.toIPv4Address() > 0 && host != QHostAddress::LocalHost) {
            int ip4 = host.toIPv4Address();
            // % is a modulo operator. It functions as a remainder of the amount after division by 256
            // >> is a bitwise shift. It shifts the bits 8 bits to the right, basically dividing it by 256 (2^8)
            int part0 = (ip4 % 256);
            int part1 = ((ip4 >> 8) % 256);
            int part2 = ((ip4 >> 16) % 256);
            int part3 = ((ip4 >> 24) % 256);
            if (part0 < 0) {
                //on linux, the modulus operator returns a negative number
                part0 += 256;
                part1 += 256;
                part2 += 256;
                part3 += 256;
            }
            ip4Addr = QString::number(part3) + "." +
                      QString::number(part2) + "." +
                      QString::number(part1) + "." +
                      QString::number(part0);
        }
    }
}

void NetworkManager::startServer(QWidget *parent) {
    server = new QTcpServer(parent);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(server, SIGNAL(destroyed()), this, SLOT(disconnected()));
    server->listen(QHostAddress::Any, port);
}

NetworkManager NetworkManager::instance;

NetworkManager& NetworkManager::getInstance() {
    return instance;
}

void NetworkManager::newConnection() {
    qDebug() << "new connection";
    QTcpSocket* socket = server->nextPendingConnection();
    isPrimary = true;
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(destroyed()), this, SLOT(disconnected()));
}

void NetworkManager::disconnected() {
}

void NetworkManager::read() {
    qDebug() << "message from other player";
    QString line;
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    while (socket->canReadLine()) {
        line = socket->readLine();
        qDebug() << "Data: " + line;
        stringstream s(line.toStdString());
        string operation;
        s >> operation;
        if (operation == "startTank") {
            int x, y, d;
            s >> x >> y >> d;
            OpponentManager::getInstance().startTankMoving(x, y, (Direction) d);
        } else if (operation == "stopTank") {
            int x, y;
            s >> x >> y;
            OpponentManager::getInstance().stopTankMoving(x, y);
        } else if (operation == "bullet") {
            int x, y;
            double angle;
            s >> x >> y >> angle;
            OpponentManager::getInstance().fireBullet(x, y, angle);
        } else if (line.startsWith("level")) {
            isPrimary = false;
            int levelNum;
            string ipAddr;
            s >> levelNum >> ipAddr;
            LevelManager::getInstance().loadLevel(levelNum, false);
            sock = new QTcpSocket(server->parent());
            sock->connectToHost(QString(ipAddr.c_str()), remotePort);
            sock->waitForConnected();
            Interface::getInstance().disableWidgets();
            emit startLevel();
        }
    }
}

void NetworkManager::connectToHost(QString ipAddr, int levelNum) {
    sock = new QTcpSocket(server->parent());
    sock->connectToHost(ipAddr, remotePort);
    sock->waitForConnected();
    sock->write(("level " + QString::number(levelNum) + " " + ip4Addr + "\n").toStdString().c_str());
}

void NetworkManager::bullet(int x, int y, double heading) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "bullet " << x << " " << y << " " << heading << "\n";
    QString data = s.str().c_str();
    sock->write(data.toLocal8Bit());
}

void NetworkManager::startTank(int x, int y, Direction d) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "startTank " << x << " " << y << " " << d << "\n";
    QString data = s.str().c_str();
    sock->write(data.toLocal8Bit());
}

void NetworkManager::stopTank(int x, int y) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "stopTank " << x << " " << y << "\n";
    QString data = s.str().c_str();
    sock->write(data.toLocal8Bit());
}

void NetworkManager::turret(double angle) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "turret " << angle << "\n";
    QString data = s.str().c_str();
    sock->write(data.toLocal8Bit());
}
