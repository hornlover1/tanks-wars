#include "networkmanager.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include "opponentmanager.h"
#include <sstream>

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent), server(new QTcpServer(this)), port(7573), remotePort(7573) {
    for (QHostAddress host: QNetworkInterface::allAddresses()) {
        ip4Addr = host.toString();
    }
    server->listen(QHostAddress::Any, port);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(server, SIGNAL(destroyed()), this, SLOT(disconnected()));
}

NetworkManager NetworkManager::instance;

NetworkManager& NetworkManager::getInstance() {
    return instance;
}

void NetworkManager::newConnection() {
    //TODO:write this method
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
    QString line;
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    while (socket->canReadLine()) {
        line = socket->readLine();
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
            OpponentManager::getInstance().setTurret(angle);
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
    stringstream s;
    s << "bullet " << x << " " << y << " " << heading;
    sock->write(s.str().c_str());
}

void NetworkManager::startTank(Direction d) {
    stringstream s;
    s << "startTank " << d;
    sock->write(s.str().c_str());
}

void NetworkManager::stopTank() {
    sock->write("stopTank");
}

void NetworkManager::turret(double angle) {
    stringstream s;
    s << "turret " << angle;
    sock->write(s.str().c_str());
}
