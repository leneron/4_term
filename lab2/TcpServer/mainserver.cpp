#include "mainserver.h"
#include <QDebug>

MainServer::MainServer()
{

}

void MainServer::startServer()
{
    if (this->listen(HOST, PORT))
    {
        qDebug() << "Server started";
    }
    else
    {
        qDebug() << "Server didn't start";
    }
}

void MainServer::removeClient(ServerClient *client)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i] == client)
        {
            delete client;
            clients.erase(clients.begin() + i);
            return;
        }
    }
}

void MainServer::updateText(ServerClient* updatedClient)
{
    qDebug() << "Updating to all clients";

    QByteArray data = updatedClient->getText().toUtf8();
    int size = data.length();

    //write this block of bytes to the socket of every client
    for (ServerClient* client : clients)
    {
        client->getSocket()->write((char*)&size, sizeof(size));
        client->getSocket()->write(data);
    }
}

void MainServer::incomingConnection(qintptr handle)
{
    ServerClient* client = new ServerClient(handle, this);

    qDebug() << handle << " client created";

    clients.push_back(client);

    //connect signal and slot
    QObject::connect(client, SIGNAL(updateText(ServerClient*)), this, SLOT(updateText(ServerClient*)), Qt::DirectConnection);
}

