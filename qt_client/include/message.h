#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

struct Message{
    QString from_username;
    QString content;

    Message(QString from_username = "", QString content = "");
};

#endif // MESSAGE_H
