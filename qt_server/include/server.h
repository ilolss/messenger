
#ifndef QT_SERVER_SERVER_H
#define QT_SERVER_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QMap>
#include "database.h"

class Server: public QTcpServer {
    Q_OBJECT

public:
    Server();

private:
//    QVector<QTcpSocket*> Sockets;
    QMap<qint32, QTcpSocket*> Sockets;
    QTcpSocket *socket;
    Database db;
    quint16 block_size;

    static const quint8 logInRequest = 1;
    static const quint8 signUpRequest = 2;
    static const quint8 authResponse = 3;
    static const quint8 sendMessageRequest = 4;
    static const quint8 getChatRequest = 5;
    static const quint8 getChatResponse = 6;
    static const quint8 updateChat = 7;
    static const quint8 getUserIdRequest = 8;
    static const quint8 userIdResponse = 9;
    static const quint8 disconnectUser = 10;

private:
    void sendToClient();
    void sendMessageResponse();
    void sendGetChatResponse(QVector<Message> messages);
    void sendAuthResponse(qint32 user_id);
    void sendUserId(qint32 user_id);
    void sendUpdateChat(qint32 user_id);

public Q_SLOTS:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif //QT_SERVER_SERVER_H
