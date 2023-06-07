//
// Created by Filipp Po on 10.05.2023.
//

#ifndef QT_SERVER_DATABASE_H
#define QT_SERVER_DATABASE_H

#include <QString>
#include "message.h"

class Database {
public:
    Database();
    ~Database();

    int getUserId(QString username);
    int logIn(QString username, QString password);
    int signUp(QString username, QString password);
    void addMessage(qint32 from_user_id, qint32 to_user_id, QString content);
    QVector<Message> getChat(qint32 first_user_id, qint32 second_user_id);

private:
    QString getUsername(qint32 user_id);
};

#endif //QT_SERVER_DATABASE_H
