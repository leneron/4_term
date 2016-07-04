#include "serverclient.h"
#include "mainserver.h"

ServerClient::ServerClient(quintptr socketDescriptor, QObject *parent):
    QObject(parent), blockSize(0)
{
    socket = new QTcpSocket(this);
    if (!socket->setSocketDescriptor(socketDescriptor))
        qDebug() << "Error happened";
    else
    {
        qDebug() << socketDescriptor  <<" descriptor is set";
    }

    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()), Qt::DirectConnection);
}

QTcpSocket *ServerClient::getSocket() const
{
    return socket;
}

void ServerClient::onSocketConnected()
{
    //actually, client is already connected
}

void ServerClient::onSocketDisconnected()
{
    qDebug() << "Server Client disconnected";
    //prevention from deleting
    getServer()->removeClient(this);
}

void ServerClient::onSocketReadyRead()
{
    qDebug() << "Reading the data";

    int size = 0;
    socket->read((char*)&size, sizeof(size));
    auto data = socket->readAll();
    if (data.length() != size)
    {
        qDebug("Rejected");
        return;
    }

    text = QString::fromUtf8(data);

    qDebug() << "OK";
    qDebug() << "Text:" << text;

    //send signal that text in client is updated
    emit updateText(this);
}

MainServer *ServerClient::getServer() const
{
    return dynamic_cast<MainServer*>(parent());
}

QString ServerClient::getText() const
{
    return text;
}

//void ServerClient::sendText(const QString &string)
//{
//    QByteArray block;
//    QDataStream sendStream(&block, QIODevice::ReadWrite);

//    sendStream << quint16(0) << string;
//    sendStream.device()->seek(0);
//    sendStream << (quint16)(block.size() - sizeof(quint16));
//    m_ptcpSocket->write(block);
//}

