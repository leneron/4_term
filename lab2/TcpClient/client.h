#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class Client: public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    QString getText() const;
    void setText(const QString &value);
    void setUserName(const QString &value);

    void sendTextToServer();
    void connect();
    void disconnect();

signals:
    void getTextFromServer();
    void clearText();

public slots:
    //Slots for handling the socket signals
    void onSocketConnected();
    void onSocketDisconnected();
    //if socket got the packet
    void onSocketReadyRead();

private:
    const QHostAddress HOST = QHostAddress::LocalHost;
    const quint16 PORT = 5555;

    //Work with socket
    QTcpSocket* socket;
    //Size of the current block of the data
    qintptr blockSize;
    //text
    QString text;
    //user name
    QString userName;
};

#endif // CLIENT_H
