#ifndef CLIENT_H
#define CLIENT_H

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
    static const quint8 sendMessageRequest = 3;
    static const quint8 getChatRequest = 4;
    static const quint8 updateChat = 5;
    static const quint8 logInResponse = 6;
    static const quint8 signUpResponse = 7;

public slots:
    void slotReadyRead();
    void slotSendLogInRequest(QString username, QString password);
    void slotSendSignUpRequest(QString username, QString password);
    void slotSendMessageRequest(quint32 user_id_to, QString text);
    void slotSendGetChatRequest(quint32 user_id_first, quint32 user_id_second);

};

#endif // CLIENT_H
