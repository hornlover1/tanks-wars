#include "networkmanager.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include "opponentmanager.h"
#include <sstream>
#include <QApplication>
#include "interface.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent), port(7573), remotePort(7573) {
    sock = nullptr;
    for (QHostAddress host: QNetworkInterface::allAddresses()) {
        if (host.toIPv4Address() > 0) {
            int ip4 = host.toIPv4Address();
            // % is a modulo operator. It functions as a remainder of the amount after division by 256
            // it seems that the c++ modulo operator returns 256 less than an actual modulo operation, so I'm adding that 256 back in
            // >> is a bitwise shift. It shifts the bits 8 bits to the right, basically dividing it by 256 (2^8)
            int part0 = (ip4 % 256) + 256;
            int part1 = ((ip4 >> 8) % 256) + 256;
            int part2 = ((ip4 >> 16) % 256) + 256;
            int part3 = ((ip4 >> 24) % 256) + 256;
            ip4Addr = QString::number(part3) + "." +
                      QString::number(part2) + "." +
                      QString::number(part1) + "." +
                      QString::number(part0);
            //don't ask me how this works. I just guessed from how it was turning out, and it worked
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
    QString line;
    while (socket->canReadLine()) {
        line = socket->readLine();
        //the sender is sending something like "level 1" to initiate the connection
        //this indicates that the sender is starting the connection and therefore they are the primary player
        if (line.startsWith("level")) {
            isPrimary = false;
            //get the characters after "level "
            line.chop(6);
            int levelNum = line.toInt();
            LevelManager::getInstance().loadLevel(levelNum, false);
        } else {
            isPrimary = true;
        }
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(destroyed()), this, SLOT(disconnected()));
}

void NetworkManager::disconnected() {
    //TODO:write this method
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
            int d;
            s >> d;
            OpponentManager::getInstance().startTankMoving((Direction) d);
        } else if (operation == "stopTank") {
            OpponentManager::getInstance().stopTankMoving();
        } else if (operation == "turret") {
            double angle;
            s >> angle;
            //OpponentManager::getInstance().setTurret(angle);
        } else if (operation == "bullet") {
            int x, y;
            double angle;
            s >> x >> y >> angle;
            OpponentManager::getInstance().fireBullet(x, y, angle);
        }
    }
}

void NetworkManager::connectToHost(QString ipAddr, int levelNum) {
    sock = new QTcpSocket(this);
    sock->write(("level " + QString::number(levelNum)).toStdString().c_str());
    sock->connectToHost(ipAddr, remotePort);
    sock->waitForConnected();
}

void NetworkManager::bullet(int x, int y, double heading) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "bullet " << x << " " << y << " " << heading;
    sock->write(s.str().c_str());
}

void NetworkManager::startTank(Direction d) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "startTank " << d;
    sock->write(s.str().c_str());
}

void NetworkManager::stopTank() {
    if (sock == nullptr) {
        return;
    }
    sock->write("stopTank");
}

void NetworkManager::turret(double angle) {
    if (sock == nullptr) {
        return;
    }
    stringstream s;
    s << "turret " << angle;
    sock->write(s.str().c_str());
}
