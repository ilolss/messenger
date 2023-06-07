#include "../include/server.h"

Server::Server() : block_size(0) {
    if (this->listen(QHostAddress::Any, 8080)) {
        qInfo() << "[INFO] server start";
    } else {
        qInfo() << "[INFO] server not start";
    }
    qDebug() << "server constructor";
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    qInfo() << "[INFO] client connection, socket descriptor: " << socketDescriptor;
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
                    QString username;
                    QString password;
                    in_stream >> username >> password;
                    qDebug() << username << password;
                    qint32 id = db.logIn(username, password);
                    qDebug() << "id " << id;
                    if (id >= 0) {
                        Sockets.insert(id, socket);
                    }
                    qDebug() << "readyRead socket: " << socket->socketDescriptor();
                    sendAuthResponse(id);
                    block_size = 0;
                    break;
                }
                case signUpRequest:
                {
                    QString username;
                    QString password;
                    in_stream >> username >> password;
                    qDebug() << username << password;
                    qint32 id = db.signUp(username, password);
                    qDebug() << "id " << id;
                    if (id >= 0) {
                        Sockets.insert(id, socket);
                    }
                    sendAuthResponse(id);
                    block_size = 0;
                    break;
                }
                case getUserIdRequest:
                {
                    QString username;
                    in_stream >> username;
                    sendUserId(db.getUserId(username));
                    block_size = 0;
                    break;
                }
                case sendMessageRequest:
                {
                    qint32 from_user_id = -1;
                    qint32 to_user_id = -1;
                    QString content;
                    in_stream >> from_user_id >> to_user_id >> content;
                    if (from_user_id >= 0 && to_user_id >= 0) {
                        db.addMessage(from_user_id, to_user_id, content);
//                        sendUpdateChat(from_user_id);
                        sendUpdateChat(to_user_id);
                    }
                    block_size = 0;
                    break;
                }
                case getChatRequest:
                {
                    qint32 first_user_id = -1;
                    qint32 second_user_id = -1;
                    in_stream >> first_user_id >> second_user_id;
                    qDebug() << "CHatRequest: " << first_user_id << " " << second_user_id;
                    if (first_user_id >= 0 && second_user_id >= 0) {
                        QVector<Message> messages = db.getChat(first_user_id, second_user_id);
                        sendGetChatResponse(messages);
                        qDebug() << "messages size" << messages.size();
                    }
                    block_size = 0;
                    break;
                }
                case disconnectUser:
                {
                    qint32 user_id;
                    in_stream >> user_id;
                    Sockets.remove(user_id);
                    qInfo() << "[INFO] disconnect user id: " << user_id;
                    block_size = 0;
                    break;
                }
            }
        } else {

        }
    } else {
        qCritical() << "[ERROR] DataStream error\n";
    }
}

void Server::sendGetChatResponse(QVector<Message> messages) {
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << getChatResponse;
    qint32 cnt_messages = messages.size();
    out_stream << cnt_messages;
    qDebug() << "sendChatResponse, size is" << messages.size();
    for (Message& message : messages) {
        out_stream << message.from_username;
        out_stream << message.content;
        qDebug() << message.content;
    }
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
//    qDebug() << "sendUserId socket: " << socket->socketDescriptor();
    socket->write(data);
}

void Server::sendAuthResponse(qint32 user_id) {
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << authResponse;
    out_stream << user_id;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    qDebug() << "sendUserId socket: " << socket->socketDescriptor();
    socket->write(data);
}

void Server::sendUserId(qint32 user_id) {
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << userIdResponse;
    out_stream << user_id;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    qDebug() << "sendUserId socket: " << socket->socketDescriptor();
    socket->write(data);
}

void Server::sendUpdateChat(qint32 user_id) {
    if (user_id < 0) {
        return;
    }
    if (!Sockets.contains(user_id)) {
        return;
    }
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << updateChat;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    Sockets.value(user_id)->write(data);
//    socket->write(data);
}
