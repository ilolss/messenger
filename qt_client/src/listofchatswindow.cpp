#include "../include/listofchatswindow.h"
#include "ui_listofchatswindow.h"
#include <QDebug>
#include "../include/globalclient.h"

ListOfChatsWindow::ListOfChatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOfChatsWindow)
{
    ui->setupUi(this);
    connect(this, &ListOfChatsWindow::disconnectSignal, GlobalClient::client, &Client::slotSendDisconnectRequest);
    connect(this, &ListOfChatsWindow::getUserIdSignal, GlobalClient::client, &Client::slotGetUserIdRequest);
    connect(GlobalClient::client, &Client::signalOpenChatWindow, this, &ListOfChatsWindow::slotOpenChatWindow);
}

ListOfChatsWindow::~ListOfChatsWindow()
{
    delete ui;
}

void ListOfChatsWindow::reject() {
    emit windowCloseSignal();
    emit disconnectSignal();
    QDialog::reject();
}

void ListOfChatsWindow::slotOpenChatWindow(qint32 partner_user_id)
{
    if (partner_user_id < 0) {
        return;
    }
//    qDebug() << "slotOpenChatWindow";
    chatWindow = new ChatWindow(this, partner_user_id);
    connect(this, &ListOfChatsWindow::windowCloseSignal, chatWindow, &ChatWindow::reject);
    chatWindow->show();
}


void ListOfChatsWindow::on_openChatButton_clicked()
{
    QString partner_username = ui->usernameLineEdit->text();
    emit getUserIdSignal(partner_username);
}

