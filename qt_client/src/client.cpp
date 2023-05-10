#include "../include/client.h"
#include <QDataStream>

Client::Client() : user_id(-1), block_size(0)
{
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1", 8080);
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

void Client::slotReadyRead()
{
    QDataStream in_stream(socket);
    in_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
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
                case updateChat:
                {
                    break;
                }
                case logInResponse:
                {
                    break;
                }
                case signUpResponse:
                {
                    break;
                }
            }
        } else {

        }
    } else {
        qDebug() << "[Warrning] in_stream is not ok, client.cpp 19 line";
    }
}

void Client::slotSendLogInRequest(QString username, QString password) {
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << logInRequest;
    out_stream << username << password;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}

void Client::slotSendSignUpRequest(QString username, QString password) {
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << signUpRequest;
    out_stream << username << password;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}

void Client::slotSendMessageRequest(quint32 user_id_to, QString text)
{
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << sendMessageRequest;
    out_stream << user_id << user_id_to;
    out_stream << text;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}

void Client::slotSendGetChatRequest(quint32 user_id_first, quint32 user_id_second)
{
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << getChatRequest;
    out_stream << user_id_first << user_id_second;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}
