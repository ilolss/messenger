#include "../include/client.h"
#include <QDataStream>

Client::Client() : user_id(-1), block_size(0)
{
    socket = new QTcpSocket;
    qDebug() << socket;
    socket->connectToHost("127.0.0.1", 8080);
    qDebug() << "Client constructor";
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
//    socket->waitForConnected();
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
                    emit signalUpdateChat();
                    block_size = 0;
                    break;
                }
                case authResponse:
                {
                    qint32 user_id;
                    in_stream >> user_id;
                    qDebug() << "[INFO] user id is " << user_id;
                    if (user_id >= 0) {
                        this->user_id = user_id;
                        emit signalOpenListOfchatWindow();
                    }
                    block_size = 0;
                    break;
                }
                case userIdResponse:
                {
                    qint32 partner_user_id;
                    in_stream >> partner_user_id;
                    qDebug() << "[INFO] partner user id is " << partner_user_id;
                    if (partner_user_id >= 0) {
                        emit signalOpenChatWindow(partner_user_id);
                    }
                    block_size = 0;
                    break;
                }
                case getChatResponse:
                {
                    qint32 cnt_message = 0;
                    in_stream >> cnt_message;
                    QVector<Message> messages;
                    while (cnt_message--) {
                        QString from_username;
                        QString content;
                        in_stream >> from_username;
                        in_stream >> content;
                        messages.push_back(Message(from_username, content));
                    }
                    emit signalGetChatResponse(messages);
                    block_size = 0;
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
    data.clear();
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

void Client::slotSendMessageRequest(qint32 user_id_to, QString text)
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
    emit signalUpdateChat();
}

void Client::slotSendGetChatRequest(qint32 user_id_second)
{
    if (user_id < 0 || user_id_second < 0) {
        return;
    }
    qDebug() << "slotSendGetChatRequest";
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << getChatRequest;
    out_stream << user_id << user_id_second;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}

void Client::slotGetUserIdRequest(QString username)
{
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << getUserIdRequest;
    out_stream << username;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}

void Client::slotSendDisconnectRequest()
{
    QByteArray data;
    QDataStream out_stream(&data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out_stream << quint16(0);
    out_stream << disconnectUser;
    out_stream << user_id;
    out_stream.device()->seek(0);
    out_stream << quint16(data.size() - sizeof(quint16));
    qDebug() << "send disconnect request, user_id is " << user_id;
    socket->write(data);
}
