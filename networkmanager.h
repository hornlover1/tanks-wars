#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "mainwindow.h"
#include <QObject>
#include <QString>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <levelobject.h>

class NetworkManager : public QObject {
    Q_OBJECT

    bool isPrimary;

    QTcpServer* server;
    QTcpSocket* sock;

    QString ip4Addr;

    int port;

    int remotePort;

    NetworkManager(QObject *parent = 0);

    static NetworkManager instance;
public:
    static NetworkManager&  getInstance();
    void connectToHost(QString ipAddr, int);
    void bullet(int x, int y, double heading);
    void startTank(Direction d);
    void stopTank();
    void turret(double angle);
private slots:
    void newConnection();
    void disconnected();
    void read();
};

#endif // NETWORKMANAGER_H
