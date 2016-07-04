#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QTcpSocket>

class MainServer;

class ServerClient: public QObject
{
    Q_OBJECT
public:
    explicit ServerClient(quintptr socketDescriptor, QObject *parent = 0);

    QTcpSocket *getSocket() const;

    QString getText() const;

   // void sendText(const QString& string);

signals:
    void updateText(ServerClient *updatedClient);

public slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketReadyRead();

private:

    MainServer* getServer() const;

    //the same as in the real client
    QTcpSocket* socket;
    quintptr blockSize;
    QString text;
};

#endif // SERVERCLIENT_H
