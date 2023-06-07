//
// Created by Filipp Po on 10.05.2023.
//
#include "../include/database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

Database::Database() {
    qDebug() << "db constructor\n";
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "messenger_db");
    db.setHostName("ep-raspy-violet-238986.us-east-2.aws.neon.tech");
    db.setPort(5432);
    db.setDatabaseName("messenger");
    db.setUserName("root");
    db.setPassword("uUdA8Vio4Cnj");
    bool is_open_connection = db.open();
    if (is_open_connection) {
        qDebug() << "[INFO] Database connection is open";
    } else {
        qDebug() << "[ERROR] " << db.lastError().text();
    }
}

Database::~Database() {
    QSqlDatabase::database("messenger_db").close();
    QSqlDatabase::removeDatabase("messenger_db");
}

qint32 Database::getUserId(QString username) {
    QSqlQuery query(QSqlDatabase::database("messenger_db"));
    query.prepare("SELECT id FROM users WHERE username = :username");
    query.bindValue(":username", username);
    bool is_insert = query.exec();
    if (!is_insert) {
        qWarning() << "[WARNING] " << query.lastError().text();
        return -1;
    }
    if (!query.size()) {
        return -1;
    }
    query.first();
    return query.value("id").toInt();
}

qint32 Database::logIn(QString username, QString password) {
    QSqlQuery query(QSqlDatabase::database("messenger_db"));
    query.prepare("SELECT id, password FROM users WHERE username = :username");
    query.bindValue(":username", username);
    bool is_insert = query.exec();
    if (!is_insert) {
        qWarning() << "[WARNING] " << query.lastError().text();
        return -1;
    }
    if (!query.size()) {
        return -1;
    }
    query.first();
    if (password != query.value("password").toString()) {
        return -1;
    }
    return query.value("id").toInt();
}

qint32 Database::signUp(QString username, QString password) {
    QSqlQuery query(QSqlDatabase::database("messenger_db"));
    query.prepare("INSERT INTO users (username, password) VALUES(:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    bool is_insert = query.exec();
    if (!is_insert) {
        qWarning() << "[WARNING] " << query.lastError().text();
        return -1;
    }
    return getUserId(username);
}

void Database::addMessage(qint32 from_user_id, qint32 to_user_id, QString content){
    QSqlQuery query(QSqlDatabase::database("messenger_db"));
    query.prepare("INSERT INTO messages (from_user_id, to_user_id, content) VALUES(:from_user_id, :to_user_id, :content)");
    query.bindValue(":from_user_id", from_user_id);
    query.bindValue(":to_user_id", to_user_id);
    query.bindValue(":content", content);
    bool is_insert = query.exec();
    if (!is_insert) {
        qWarning() << "[WARNING] " << query.lastError().text();
    }
}

QVector<Message> Database::getChat(qint32 first_user_id, qint32 second_user_id) {
    QSqlQuery query(QSqlDatabase::database("messenger_db"));
//    query.prepare("SELECT from_user_id, content FROM messages "
//                  "WHERE (from_user_id = :first_user_id AND to_user_id = :second_user_id) "
//                  "OR (from_user_id = :second_user_id AND to_user_id = :first_user_id)"
//                  );
//    query.prepare("SELECT *");
    query.prepare("SELECT users.username, messages.content FROM messages JOIN users ON messages.from_user_id = users.id AND ((messages.from_user_id = :first_user_id AND messages.to_user_id = :second_user_id) OR (messages.from_user_id = :second_user_id AND messages.to_user_id = :first_user_id))");
    query.bindValue(":first_user_id", first_user_id);
    query.bindValue(":second_user_id", second_user_id);
    bool is_insert = query.exec();
    QVector<Message> messages;
    if (!is_insert) {
        qWarning() << "[WARNING]" << query.lastError().text();
        return messages;
    }
    while(query.next()) {
        messages.push_back(Message(
                query.value("username").toString(),
                query.value("content").toString())
                );
    }
    return messages;
}

//QString Database::getUsername(qint32 user_id) {
//    QSqlQuery query(QSqlDatabase::database("messenger_db"));
//    query.prepare("SELECT username FROM users WHERE id = :user_id");
//    query.bindValue(":user_id", user_id);
//    bool is_ok = query.exec();
//    if (!is_ok) {
//        qWarning() << "[WARNING] " << query.lastError().text();
//        return "";
//    }
//    if (!query.size()) {
//        return "";
//    }
//    query.first();
//    return query.value("username").toString();
//}

