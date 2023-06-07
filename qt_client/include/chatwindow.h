#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include "message.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr, qint32 partner_user_id = -1);
    ~ChatWindow();

private slots:
    void on_sendMessageButton_clicked();

    void slotDisplayMessages(QVector<Message> messages);
    void slotUpdateChat();

signals:
    void sendMessageSignal(qint32 user_id_to, QString text);
    void getChatSignal(qint32 partner_user_id);

private:
    Ui::ChatWindow *ui;
    qint32 partner_user_id;
    void fetchChat();
};

#endif // CHATWINDOW_H
