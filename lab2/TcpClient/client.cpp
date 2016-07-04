#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
}

QString Client::getText() const
{
    return text;
}

void Client::setText(const QString &value)
{
    text = value;
}

void Client::onSocketConnected()
{
    QByteArray block;
    QDataStream outStream(&block, QIODevice::ReadWrite);

    //2 bytes for the size
    //next bytes - authentication name

    //there should be MainClient::commandSendToServer instead of 2
    outStream << quint16(0) << quint8(2) << userName;

    //go to the beginning of the stream and white the size of the block
    outStream.device()->seek(0);
    outStream << quint16(block.size() - sizeof(quint16));

    //write this block of bytes to the socket
    socket->write(block);
}

void Client::onSocketDisconnected()
{
    qDebug() << userName << " disconnected";
    emit clearText();
}

void Client::onSocketReadyRead()
{
    int size = 0;
    socket->read((char*)&size, sizeof(size));
    auto data = socket->readAll();
    if (data.length() != size)
    {
        qDebug("Rejected");
        return;
    }

    text = QString::fromUtf8(data);
    qDebug() << "Received: " << text;

    emit getTextFromServer();
}

void Client::setUserName(const QString &value)
{
    userName = value;
}

void Client::sendTextToServer()
{
    qDebug() << "Sending text";

    QByteArray data = getText().toUtf8();
    int size = data.length();
    socket->write((char*)&size, sizeof(size));
    socket->write(data);
}

void Client::connect()
{
    socket->connectToHost(HOST, PORT);
}

void Client::disconnect()
{
    socket->disconnectFromHost();
}

