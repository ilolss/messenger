#include <QCoreApplication>
#include <QDebug>
#include <QTcpServer>
#include "../include/server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server server;
    qDebug() << "Hello World";
    return QCoreApplication::exec();
}
