//
// Created by Filipp Po on 10.05.2023.
//
#include "../include/database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

Database::Database() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "messenger_db");
    db.setHostName("containers-us-west-205.railway.app");
    db.setDatabaseName("railway");
    db.setUserName("postgres");
    db.setPassword("4egUQSBG77KZ4geR5Qh7");
    bool is_open_connection = db.open();
    if (is_open_connection) {
        qDebug() << "[INFO] Database connection is open\n";
    } else {
        qDebug() << "[ERROR] Database connection is not open\n";
    }
}

Database::~Database() {
    QSqlDatabase::removeDatabase("messenger_db");
}

int Database::getUserId(QString username) {
    return 0;
}

int Database::logIn(QString username, QString password) {
    return 0;
}

int Database::signUp(QString username, QString password) {

    return 0;
}

