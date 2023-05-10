#include "../include/server.h"

Server::Server() : block_size(0) {
    if (this->listen(QHostAddress::Any, 8080)) {
        qDebug() << "[INFO] server start\n";
    } else {
        qDebug() << "[INFO] server not start\n";
    }
    db = Database();
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "[INFO] client connection, socket descriptor: " << socketDescriptor << "\n";
}

void Server::slotReadyRead() {
    socket = qobject_cast<QTcpSocket *>(QObject::sender());
    QDataStream in_stream(socket);
    in_stream.setVersion(QDataStream::Qt_6_0);
    if (in_stream.status() == QDataStream::Ok) {
        if (block_size == 0) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                return;
            }
            in_stream >> block_size;
            if (socket->bytesAvailable() < block_size) {
                return;
            }
            quint8 command;
            in_stream >> command;
            switch(command) {
                case logInRequest:
                {
                    break;
                }
                case signUpRequest:
                {
                    QString username;
                    QString password;
                    in_stream >> username >> password;
                    qDebug() << username << password;
                    break;
                }
                case sendMessageRequest:
                {
                    break;
                }
                case getChatRequest:
                {
                    break;
                }
            }
        } else {

        }
    } else {
        qDebug() << "[ERROR] DataStream error\n";
    }
}

void Server::sendUserId(qint32 user_id) {

}
