#include <iostream>
#include <QCoreApplication>
#include "mainserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainServer server;
    server.startServer();

    return a.exec();
}

