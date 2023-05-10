//
// Created by Filipp Po on 10.05.2023.
//

#ifndef QT_SERVER_DATABASE_H
#define QT_SERVER_DATABASE_H

#include <QString>

class Database {
public:
    Database();
    ~Database();

    int getUserId(QString username);
    int logIn(QString username, QString password);
    int signUp(QString username, QString password);

};

#endif //QT_SERVER_DATABASE_H
