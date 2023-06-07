#ifndef CLIENT_H
#define CLIENT_H

#include "message.h"
#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();

private:
    QTcpSocket* socket;
    qint32 user_id;
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

public slots:
    void slotReadyRead();
    void slotSendLogInRequest(QString username, QString password);
    void slotSendSignUpRequest(QString username, QString password);
    void slotSendMessageRequest(qint32 user_id_to, QString text);
    void slotSendGetChatRequest(qint32 user_id_second);
    void slotGetUserIdRequest(QString username);
    void slotSendDisconnectRequest();

signals:
    void signalOpenListOfchatWindow();
    void signalOpenChatWindow(qint32 partner_user_id);
    void signalGetChatResponse(QVector<Message> messages);
    void signalUpdateChat();

};

#endif // CLIENT_H
