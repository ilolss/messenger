
#ifndef QT_SERVER_SERVER_H
#define QT_SERVER_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include "database.h"

class Server: public QTcpServer {
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> Sockets;
    Database db;
    quint16 block_size;

    static const quint8 logInRequest = 1;
    static const quint8 signUpRequest = 2;
    static const quint8 sendMessageRequest = 3;
    static const quint8 getChatRequest = 4;
    static const quint8 updateChat = 5;
    static const quint8 logInResponse = 6;
    static const quint8 signUpResponse = 7;

private:
    void sendToClient();
    void sendMessageResponse();
    void sendGetChatResponse();
    void sendUserId(qint32 user_id);
    void sendUpdateChat();

public Q_SLOTS:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif //QT_SERVER_SERVER_H
