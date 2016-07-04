#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QVector>
#include <QSignalMapper>
#include "serverclient.h"

class MainServer: public QTcpServer
{
    Q_OBJECT
public:
    explicit MainServer();

    void startServer();
    void removeClient(ServerClient* client);

signals:

public slots:
    void updateText(ServerClient *updatedClient);

protected:
    void incomingConnection(qintptr handle) override;

private:
    const QHostAddress HOST = QHostAddress::LocalHost;
    const quint16 PORT = 5555;

    QVector<ServerClient*> clients;
};

#endif // MAINSERVER_H
