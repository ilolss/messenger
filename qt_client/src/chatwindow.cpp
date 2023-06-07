#include "../include/chatwindow.h"
#include "ui_chatwindow.h"
#include <QDebug>
#include "../include/globalclient.h"

ChatWindow::ChatWindow(QWidget *parent, qint32 partner_user_id) :
    QDialog(parent),
    ui(new Ui::ChatWindow),
    partner_user_id(partner_user_id)
{
    ui->setupUi(this);
//    qDebug() << "ChatWindow constructor partner user id is " << partner_user_id;
    connect(this, &ChatWindow::sendMessageSignal, GlobalClient::client, &Client::slotSendMessageRequest);
    connect(this, &ChatWindow::getChatSignal, GlobalClient::client, &Client::slotSendGetChatRequest);
    connect(GlobalClient::client, &Client::signalGetChatResponse, this, &ChatWindow::slotDisplayMessages);
    connect(GlobalClient::client, &Client::signalUpdateChat, this, &ChatWindow::slotUpdateChat);
    fetchChat();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_sendMessageButton_clicked()
{
    QString message_content = ui->MessageInput->text();
    if (partner_user_id >= 0) {
        emit sendMessageSignal(partner_user_id, message_content);
    }
}

void ChatWindow::slotDisplayMessages(QVector<Message> messages)
{
    qDebug() << "DispalyMessage: " << messages.size();
    for(Message& message : messages) {
        qDebug() << message.content;
        QString itemContent = message.from_username;
        itemContent += ": ";
        itemContent += message.content;
        ui->chatListWidget->addItem(itemContent);
    }
}

void ChatWindow::slotUpdateChat()
{
    ui->chatListWidget->clear();
    fetchChat();
}

void ChatWindow::fetchChat()
{
    if (partner_user_id > 0) {
        emit getChatSignal(partner_user_id);
        qDebug() << "Fetch data";
    }
}

